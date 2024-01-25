#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

inline void printStringContainer(const std::vector<std::string>& stringContainer)
{
    for (const auto& str : stringContainer)
    {
        std::cout << str << '\n';
    }
}

bool compareByLength(const std::string& str1, const std::string& str2)
{
    return str1.length() < str2.length();
}

class LengthComparator
{
public:
    bool operator()(const std::string& str1, const std::string& str2)
    {
        return str1.length() < str2.length();
    }
};

size_t countDivisibleBy(const std::vector<int>& vec, int number)
{
    return std::count_if(vec.begin(), vec.end(), [number](int val) -> bool {
        return (val % number == 0);
    });
}

int main()
{
    /* Task 1 */
    std::vector<std::string> stringContainer = {
        "xx",
        "xxx",
        "x",
        "xxxxx",
        "xxxx"
    };
    printStringContainer(stringContainer);
    std::cout << "\nSorting...\n\n";
    std::sort(stringContainer.begin(), stringContainer.end(), compareByLength);
    printStringContainer(stringContainer);
    std::cout << '\n';

    /* Task 2 */
    stringContainer = {
        "xx",
        "xxx",
        "x",
        "xxxxx",
        "xxxx"
    };
    printStringContainer(stringContainer);
    std::cout << "\nSorting...\n\n";
    std::sort(stringContainer.begin(), stringContainer.end(), LengthComparator());
    printStringContainer(stringContainer);
    std::cout << '\n';

    /* Task 3 */
    stringContainer = {
        "xx",
        "xxx",
        "x",
        "xxxxx",
        "xxxx"
    };
    printStringContainer(stringContainer);
    std::cout << "\nSorting...\n\n";
    std::sort(stringContainer.begin(), stringContainer.end(), [](const std::string& str1, const std::string& str2) -> bool {
        return str1.length() < str2.length();
    });
    printStringContainer(stringContainer);
    std::cout << '\n';

    /* Task 4 */
    const std::vector<int> vec = {10, 15, 20, 25, 30, 35, 40};
    const int divider = 10;
    const size_t countDiv = countDivisibleBy(vec, divider);
    std::cout << "vec:";
    for (const int val : vec)
    {
        std::cout << ' ' << val;
    }
    std::cout << "\nAmount of elements divisible by " << divider << ": " << countDiv << '\n';
    assert(countDiv == 4);

    return 0;
}
