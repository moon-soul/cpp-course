#include "arr.h"

#include <iostream>
#include <limits>

void fillArray(int numbers[], int size)
{
    std::cout << "\nFill array\n";
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Element [" << i << "]: ";
        std::cin >> numbers[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printArray(const int numbers[], int size)
{
    std::cout << "\nArray:";
    for (int i = 0; i < size; ++i)
    {
        std::cout << ' ' << numbers[i];
    }
    std::cout << '\n';
}

void translateArray(int numbers[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (numbers[i] > 0)
        {
            numbers[i] *= 2;
        }
        else if (numbers[i] < 0)
        {
            numbers[i] = 0;
        }
    }
}
