#include <algorithm>
#include <cstddef>
#include <iostream>

constexpr std::size_t ROWS = 3;
constexpr std::size_t COLS = 3;

enum class SortingDirection
{
    ByRows,
    ByColumns
};

void printArray(const int* arr, std::size_t size)
{
    std::cout << '\n';
    for (std::size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

void bubbleSort(int* arr, std::size_t size)
{
    bool swapped;
    for (std::size_t i = size; i > 1; --i)
    {
        swapped = false;
        for (std::size_t j = 1; j < i; ++j)
        {
            if (arr[j - 1] > arr[j])
            {
                std::swap(arr[j - 1], arr[j]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void print2dArray(const int arr[ROWS][COLS])
{
    std::cout << '\n';
    for (std::size_t i = 0; i < ROWS; ++i)
    {
        for (std::size_t j = 0; j < COLS; ++j)
        {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void sort(int arr[ROWS][COLS], SortingDirection direction)
{
    if (direction == SortingDirection::ByColumns)
    {
        for (std::size_t j = 0; j < COLS; ++j)
        {
            int tmp[ROWS];
            for (std::size_t i = 0; i < ROWS; ++i)
            {
                tmp[i] = arr[i][j];
            }
            std::sort(tmp, tmp + ROWS);
            for (std::size_t i = 0; i < ROWS; ++i)
            {
                arr[i][j] = tmp[i];
            }
        }
    }
    else
    {
        for (std::size_t i = 0; i < ROWS; ++i)
        {
            std::sort(arr[i], arr[i + 1]);
        }
    }
}

int main()
{
    /* Task 1 */
    const std::size_t arrSize = 5;
    int arr[arrSize] = {5, 1, 9, 7, 3};
    std::cout << "Bubble sort:";
    printArray(arr, arrSize);
    bubbleSort(arr, arrSize);
    std::cout << "\nResult:";
    printArray(arr, arrSize);

    /* Task 2 */
    int arr1[ROWS][COLS] = {
        {1, 5, 4},
        {3, 8, 6},
        {9, 5, 1}
    };
    int arr2[ROWS][COLS] = {
        {1, 5, 4},
        {3, 8, 6},
        {9, 5, 1}
    };
    std::cout << "\nSort by rows:";
    print2dArray(arr1);
    sort(arr1, SortingDirection::ByRows);
    std::cout << "\nResult:";
    print2dArray(arr1);
    std::cout << "\nSort by columns:";
    print2dArray(arr2);
    sort(arr2, SortingDirection::ByColumns);
    std::cout << "\nResult:";
    print2dArray(arr2);

    /* Task 3 */
    // Time complexity: ROWS * log2(COLUMNS) =~ O(n log(n))
    // Space complexity: O(1)

    return 0;
}
