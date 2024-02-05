#include "line_manip.hpp"

#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

size_t uniqueWordsCount(const std::string& line)
{
    if (line.empty())
    {
        return 0;
    }
    std::unordered_set<std::string> words;
    std::istringstream iss(line);
    std::string buffStr;
    while (iss >> buffStr)
    {
        words.emplace(buffStr);
    }
    return words.size();
}

std::string mostOccurredWords(const std::string& line)
{
    if (line.empty())
    {
        return "";
    }
    std::unordered_map<std::string, size_t> wordsCount;
    std::istringstream iss(line);
    std::string buffStr;
    while (iss >> buffStr)
    {
        ++wordsCount[buffStr];
    }
    std::string result;
    size_t maxCount = 1;
    for (const auto& [word, count] : wordsCount)
    {
        if (count < maxCount)
        {
            continue;
        }
        if (count > maxCount)
        {
            maxCount = count;
            result.erase();
        }
        result.append(word);
    }
    return result;
}

inline char getPair(char c)
{
    switch (c)
    {
    case ')': return '(';
    case ']': return '[';
    case '}': return '{';
    default: return '\0';
    }
}

bool isBalanced(const std::string& line)
{
    if (line.empty())
    {
        return false;
    }
    std::stack<char> brackets;
    const size_t lineLength = line.length();
    for (size_t i = 0; i < lineLength; ++i)
    {
        switch (line[i])
        {
        case '(':
        case '[':
        case '{':
            brackets.push(line[i]);
            break;
        case ')':
        case ']':
        case '}':
            if (brackets.top() != getPair(line[i])) return false;
            brackets.pop();
            break;
        default:
            continue;
        }
    }
    return brackets.empty();
}
