#include <iostream>
#include <iomanip>

#include "arr.h"
#include "str.h"

int main()
{
    /* Task 1 */
    const int arrSize = 10;
    int arr[arrSize] = {};
    fillArray(arr, arrSize);
    printArray(arr, arrSize);
    translateArray(arr, arrSize);
    printArray(arr, arrSize);

    /* Task 2 */
    const int strSize = 256;
    char str[strSize];
    std::cout << "\nEnter string: ";
    std::cin.getline(str, strSize);
    toUppercase(str);
    std::cout << "\nTo uppercase: " << str << std::endl;

    /* Task 3 */
    std::cout << "\nEnter string: ";
    std::cin.getline(str, strSize);
    std::cout << "\nString is palindrome: "
              << std::boolalpha << isPalindrome(str) << std::endl;

    /* Task 4 */
    int vowels = 0;
    int consonants = 0;
    std::cout << "\nEnter string: ";
    std::cin.getline(str, strSize);
    parseStringLetters(str, vowels, consonants);
    std::cout << "\nVowels: " << vowels
              << "\nConsonants: " << consonants
              << std::endl;

    /* Task 5 */
    char str1[strSize];
    std::cout << "\nEnter first string: ";
    std::cin.getline(str, strSize);
    std::cout << "Enter second string: ";
    std::cin.getline(str1, strSize);
    std::cout << "\nStrings are equal: "
              << std::boolalpha << isEqual(str, str1) << std::endl;

    return 0;
}
