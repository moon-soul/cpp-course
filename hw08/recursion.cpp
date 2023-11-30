#include "recursion.h"

#include <iostream>

int factorialRecursion(int count)
{
    if (count == 0)
    {
        return 1;
    }
    return count * factorialRecursion(count - 1);
}

void printNaturalNumbersRecursionAscending(int count)
{
    if (count >= 1)
    {
        printNaturalNumbersRecursionAscending(count - 1);
        std::cout << count << ' ';
    }
}

void printNaturalNumbersRecursionDescending(int count)
{
    if (count >= 1)
    {
        std::cout << count << ' ';
        printNaturalNumbersRecursionDescending(count - 1);
    }
}
