#include "loop.h"

#include <iostream>

int factorialLoop(int count)
{
    int factorial = 1; // both 0! and 1!
    for (int i = 2; i <= count; ++i)
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
