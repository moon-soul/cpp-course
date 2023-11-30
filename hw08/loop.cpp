#include "loop.h"

#include <iostream>

int factorialLoop(int count)
{
    int factorial = 1; // 0!; i = 0
    for (int i = 1; i <= count; ++i)
    {
        factorial *= i;
    }
    return factorial;
}

void printNaturalNumbersLoopAscending(int count)
{
    for (int i = 1; i <= count; ++i)
    {
        std::cout << i << ' ';
    }
}

void printNaturalNumbersLoopDescending(int count)
{
    for (int i = count; i > 0; --i)
    {
        std::cout << i << ' ';
    }
}
