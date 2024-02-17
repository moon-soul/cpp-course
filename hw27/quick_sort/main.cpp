#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int> generateVector(int size)
{
    std::vector<int> vec;
    vec.reserve(size);
    for (int i = 0; i < size; ++i)
    {
        vec.push_back(std::rand());
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
    if (size < 100'000) return 2;
    if (size < 1'000'000) return 4;
    if (size < 10'000'000) return 8;
    return std::thread::hardware_concurrency(); // Use all available hardware concurrency for very large sizes
}

void quickSort(std::vector<int>& vec, int left, int right, int depthLimit = 1)
{
    if (left < right)
    {
        if (depthLimit == 0)
        {
            depthLimit = optimalDepthLimit(vec.size());
        }
        int partitioned = partition(vec, left, right);
        if (depthLimit > 1)
        {
            std::thread leftThread(quickSort, std::ref(vec), left, partitioned - 1, depthLimit - 1);
            std::thread rightThread(quickSort, std::ref(vec), partitioned + 1, right, depthLimit - 1);
            leftThread.join();
            rightThread.join();
        }
        else
        {
            sequentialQuickSort(vec, left, partitioned - 1);
            sequentialQuickSort(vec, partitioned + 1, right);
        }
    }
}

int main()
{
    std::srand(std::time(nullptr));

    // auto vec0 = generateVector(1'000);
    // auto vec1 = generateVector(10'000);
    // auto vec2 = generateVector(100'000);
    // auto vec3 = generateVector(1'000'000);
    // auto vec4 = generateVector(10'000'000);
    // auto vec5 = generateVector(100'000'000);
    auto vec6 = generateVector(1'000'000'000);

    const auto begin = std::chrono::high_resolution_clock::now();
    quickSort(vec6, 0, vec6.size() - 1, 0); // Use 0 to indicate automatic depth limit
    const auto end = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "Duration: " << duration.count() << '\n';

    return 0;
}
