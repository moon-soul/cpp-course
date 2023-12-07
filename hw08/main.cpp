#include <iostream>

#include "loop.h"
#include "recursion.h"

void determineNumberSign(int inputs)
{
    int positives = 0;
    int zeroes = 0;
    int negatives = 0;
    for (int i = 0; i < inputs; ++i)
    {
        int number;
        std::cout << "Enter number: ";
        std::cin >> number;
        if (number > 0)
        {
            positives++;
        }
        else if (number == 0)
        {
            zeroes++;
        }
        else
        {
            negatives++;
        }
    }
    std::cout << "\nPositives: " << positives
              << "\nZeroes: " << zeroes
              << "\nNegatives: " << negatives
              << '\n';
}

int main()
{
    /* Task 1 */
    int inputs = 0;
    std::cout << "Enter amount of inputs: ";
    std::cin >> inputs;
    if (inputs > 0)
    {
        determineNumberSign(inputs);
    }
    else
    {
        std::cout << "\nInvalid amount of inputs.\n";
    }

    /* Task 2 */
    int count = 0;
    std::cout << "\nEnter factorial number: ";
    std::cin >> count;
    if (count >= 0)
    {
        std::cout << '\n' << count << "! (factorial): " << factorialLoop(count)
                  << '\n' << count << "! (factorial): " << factorialRecursion(count)
                  << '\n';
    }
    else
    {
        std::cout << "\nInvalid factorial number.\n";
    }

    /* Task 3 */
    int n = 0;
    std::cout << "\nEnter amount of natural numbers: ";
    std::cin >> n;
    if (n > 0)
    {
        std::cout << "\nAscending: ";
        printNaturalNumbersLoopAscending(n);
        std::cout << "\nAscending: ";
        printNaturalNumbersRecursionAscending(n);
        std::cout << "\nDescending: ";
        printNaturalNumbersLoopDescending(n);
        std::cout << "\nDescending: ";
        printNaturalNumbersRecursionDescending(n);
        std::cout << '\n';
    }
    else
    {
        std::cout << "\nInvalid amount of natural numbers.\n";
    }

    return 0;
}
