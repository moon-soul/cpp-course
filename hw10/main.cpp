#include <iostream>
#include <iomanip>

void swapRef(int& a, int& b)
{
    const int tmp = a;
    a = b;
    b = tmp;
}

void swapPtr(int* a, int* b)
{
    const int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool calculateSum(const double* arr, int size, double& sum)
{
    if (size < 1)
    {
        return false;
    }
    for (int i = 0; i < size; ++i)
    {
        sum += arr[i];
    }
    return true;
}

bool find1(const int* arr, int size, int toFind)
{
    for (int i = 0; i < size; ++i)
    {
        if (*(arr + i) == toFind)
        {
            return true;
        }
    }
    return false;
}

bool find2(const int* arr, int size, int toFind)
{
    const int* last = arr + size - 1;
    for ( ; arr <= last; ++arr)
    {
        if (*arr == toFind)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    /* Task 1 */
    int a = 0;
    int b = 0;
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;
    std::cout << "\na: " << a << "\nb: " << b << '\n';
    swapRef(a, b);
    std::cout << "\na: " << a << "\nb: " << b << '\n';
    swapPtr(&a, &b);
    std::cout << "\na: " << a << "\nb: " << b << '\n';

    /* Task 2 */
    double sum = 0.0;
    const int arrSize = 10;
    const double arr[arrSize] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    calculateSum(arr, arrSize, sum);
    std::cout << "\nSum: " << sum << '\n';

    /* Task 3 */
    int toFind = 0;
    const int arr1[arrSize] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "\nEnter number to find: ";
    std::cin >> toFind;
    std::cout << "\nNumber " << toFind << " is found: "
              << std::boolalpha << find1(arr1, arrSize, toFind);
    std::cout << "\nNumber " << toFind << " is found: "
              << std::boolalpha << find2(arr1, arrSize, toFind) << '\n';

    return 0;
}
