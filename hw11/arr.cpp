#include "arr.hpp"

#include <iostream>

#include "sorting_direction.hpp"

void printArray(const int* arr, int size)
{
    std::cout << "\nArray:";
    for (int i = 0; i < size; ++i)
    {
        std::cout << ' ' << arr[i];
    }
}

bool compare(int a, int b, SortingDirection direction)
{
    if (direction == SortingDirection::Descending)
    {
        return a > b;
    }
    return a < b;
}

bool isSorted(const int* arr, int size, SortingDirection direction)
{
    for (int i = 1; i < size; ++i)
    {
        if (!compare(arr[i - 1], arr[i], direction))
        {
            return false;
        }
    }
    return true;
}
