#include "str.h"

#include <cctype>
#include <cstring>

void toUppercase(char str[])
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (std::islower(str[i]))
        {
            str[i] = std::toupper(str[i]);
        }
    }
}

bool isPalindrome(const char str[])
{
    for (int i = 0, j = (std::strlen(str) - 1); i < j; ++i, --j)
    {
        if (str[i] != str[j])
        {
            return false;
        }
    }
    return true;
}

void parseStringLetters(const char str[], int& vowelsCount, int& consonantsCount)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (!std::isalpha(str[i]))
        {
            continue;
        }
        switch (str[i])
        {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            vowelsCount++;
            break;
        default:
            consonantsCount++;
            break;
        }
    }
}

bool isEqual(const char str1[], const char str2[])
{
    for (int i = 0; (str1[i] != '\0') || (str2[i] != '\0'); ++i)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}
