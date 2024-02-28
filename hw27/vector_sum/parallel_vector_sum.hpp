#pragma once

#include <cassert>
#include <cstddef>
#include <thread>
#include <vector>

template<class Type>
int64_t parallelVectorSum(const std::vector<Type>& vec, size_t threadsNum = 2)
{
    assert(threadsNum > 0);

    const auto worker = [](const std::vector<Type>& chunk, size_t start, size_t end, int64_t& sum)
    {
        for (auto pos = chunk.cbegin() + start; pos != chunk.cbegin() + end; ++pos)
        {
            sum += *pos;
        }
    };

    int64_t result = Type{};

    if (threadsNum == 1)
    {
        worker(vec, 0, vec.size(), result);
        return result;
    }

    std::vector<std::thread> threads;
    threads.reserve(threadsNum);

    std::vector<int64_t> partialSums;
    partialSums.resize(threadsNum);

    const size_t chunkSize = vec.size() / threadsNum;

    for (size_t i = 0; i < threadsNum; ++i)
    {
        const size_t start = i * chunkSize;
        const size_t end = (i == threadsNum - 1) ? vec.size() : start + chunkSize;
        threads.emplace_back(worker, std::cref(vec), start, end, std::ref(partialSums[i]));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    for (int64_t sum : partialSums)
    {
        result += sum;
    }
    return result;
}
