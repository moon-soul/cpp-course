#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

#include "parallel_vector_sum.hpp"

int main()
{
    std::vector<size_t> vec1;
    vec1.resize(10'000, 1);

    std::vector<size_t> vec2;
    vec2.resize(100'000, 1);

    std::vector<size_t> vec3;
    vec3.resize(1'000'000, 1);

    std::vector<size_t> vec4;
    vec4.resize(10'000'000, 1);

    std::vector<size_t> vec5;
    vec5.resize(100'000'000, 1);

    std::vector<size_t> vec6;
    vec6.resize(1'000'000'000, 1);

    const auto begin = std::chrono::high_resolution_clock::now();
    const auto result = parallelVectorSum(vec6, 2 * std::thread::hardware_concurrency());
    const auto end = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "Duration: " << duration.count() << "\nResult: " << result << '\n';

    return 0;
}
