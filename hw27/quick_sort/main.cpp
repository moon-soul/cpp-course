#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int> generateVector(int size)
{
    std::vector<int> vec;
    vec.reserve(size);
    for (int i = size; i > 0; --i)
    {
        vec.push_back(i);
    }
    return vec;
}

inline int partition(std::vector<int>& vec, int left, int right)
{
    int pivot = vec[right];
    int i = left - 1;
    for (int j = left; j < right; ++j)
    {
        if (vec[j] < pivot)
        {
            std::swap(vec[++i], vec[j]);
        }
    }
    std::swap(vec[++i], vec[right]);
    return i;
}

inline void sequentialQuickSort(std::vector<int>& vec, int left, int right)
{
    if (left < right)
    {
        int partitioned = partition(vec, left, right);
        sequentialQuickSort(vec, left, partitioned - 1);
        sequentialQuickSort(vec, partitioned + 1, right);
    }
}

/* Based on the experimental discoveries */
inline int optimalDepthLimit(int size)
{
    if (size < 10'000) return 1; // Use sequential sort for small sizes
    if (size < 100'000) return std::min(2u, std::thread::hardware_concurrency());
    if (size < 1'000'000) return std::min(4u, std::thread::hardware_concurrency());
    if (size < 10'000'000) return std::min(8u, std::thread::hardware_concurrency());
    return std::thread::hardware_concurrency(); // Use all available hardware concurrency for very large sizes
}

void quickSort(std::vector<int>& vec, int left, int right, int threadLimit = 1)
{
    const int limit = (threadLimit == 0) ? optimalDepthLimit(vec.size()) : threadLimit;
    if (limit <= 1)
    {
        sequentialQuickSort(vec, left, right);
        return;
    }
    std::atomic<int> availableThreads{limit};
    std::function<void(int, int, std::atomic<int>&)> quickSortParallel = [&](int l, int r, std::atomic<int>& threads)
    {
        if (l < r)
        {
            const int partitioned = partition(vec, l, r);
            std::thread leftThread;
            std::thread rightThread;
            if (threads.fetch_sub(1, std::memory_order_relaxed) > 0)
            {
                leftThread = std::thread([&]() { quickSortParallel(l, partitioned - 1, threads); });
            }
            else
            {
                threads.fetch_add(1, std::memory_order_relaxed);
                sequentialQuickSort(vec, l, partitioned - 1);
            }
            if (threads.fetch_sub(1, std::memory_order_relaxed) > 0)
            {
                rightThread = std::thread([&]() { quickSortParallel(partitioned + 1, r, threads); });
            }
            else
            {
                threads.fetch_add(1, std::memory_order_relaxed);
                sequentialQuickSort(vec, partitioned + 1, r);
            }
            if (leftThread.joinable()) leftThread.join();
            if (rightThread.joinable()) rightThread.join();
        }
    };
    quickSortParallel(left, right, availableThreads);
}

int main()
{
    // auto vec0 = generateVector(1'000);
    // auto vec1 = generateVector(10'000);
    // auto vec2 = generateVector(100'000);
    // auto vec3 = generateVector(1'000'000);
    // auto vec4 = generateVector(10'000'000);
    auto vec5 = generateVector(100'000'000);

    const auto begin = std::chrono::high_resolution_clock::now();
    quickSort(vec5, 0, vec5.size() - 1, 0); // Use 0 to indicate automatic depth limit
    const auto end = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "Duration: " << duration.count() << '\n';

    return 0;
}
