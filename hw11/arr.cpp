#include "arr.hpp"

#include <iostream>

void printArray(const int* arr, int size)
{
    std::cout << "\nArray:";
    for (int i = 0; i < size; ++i)
    {
        std::cout << ' ' << arr[i];
    }
}

bool isSorted(const int* arr, int size, SortingDirection direction)
{
    if (direction == SortingDirection::Descending)
    {
        for (int i = 1; i < size; ++i)
        {
            if (arr[i - 1] < arr[i])
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = 1; i < size; ++i)
        {
            if (arr[i - 1] > arr[i])
            {
                return false;
            }
        }
    }
    return true;
}
