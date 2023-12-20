#include <iostream>
#include <iomanip>

#include "arr.hpp"

const int ROWS = 4;
const int COLS = 6;

bool find(const int arr2d[ROWS][COLS], int toFind)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (arr2d[i][j] == toFind)
            {
                return true;
            }
        }
    }
    return false;
}

void traverseTopDownRightLeftByColumns(const int arr2d[ROWS][COLS])
{
    std::cout << '\n';
    for (int j = COLS - 1; j >= 0; --j)
    {
        for (int i = 0; i < ROWS; ++i)
        {
            std::cout << arr2d[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void traverseLeftRightDownTopSwitchingByRows(const int arr2d[ROWS][COLS])
{
    std::cout << '\n';
    for (int i = ROWS - 1; i >= 0; --i)
    {
        if (i & 1)
        {
            for (int j = 0; j < COLS; ++j)
            {
                std::cout << arr2d[i][j] << ' ';
            }
        }
        else
        {
            for (int j = COLS - 1; j >= 0; --j)
            {
                std::cout << arr2d[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main()
{
    /* Task 1 */
    const int arr2d[ROWS][COLS] = {
        {6, 8, 2, 7, 3, 1},
        {9, 4, 1, 3, 5, 8},
        {0, 6, 9, 5, 1, 4},
        {1, 4, 0, 3, 7, 9}
    };
    int toFind = 0;
    std::cout << "Enter number to find: ";
    std::cin >> toFind;
    std::cout << "\nNumber " << toFind << " is found: "
              << std::boolalpha << find(arr2d, toFind) << '\n';

    /* Task 2 */
    const int arrSize = 10;
    const int arr[arrSize] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int arr1[arrSize] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    printArray(arr, arrSize);
    std::cout << " is sorted in ascending order: "
              << isSorted(arr, arrSize, SortingDirection::Ascending);
    printArray(arr1, arrSize);
    std::cout << " is sorted in ascending order: "
              << isSorted(arr1, arrSize, SortingDirection::Ascending);
    printArray(arr1, arrSize);
    std::cout << " is sorted in descending order: "
              << isSorted(arr1, arrSize, SortingDirection::Descending) << '\n';

    /* Task 3 */
    traverseTopDownRightLeftByColumns(arr2d);
    traverseLeftRightDownTopSwitchingByRows(arr2d);

    return 0;
}
