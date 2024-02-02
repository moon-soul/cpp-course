#pragma once

#include <string>
#include <vector>

namespace Wordle
{

enum class GuessTransformResult
{
    LengthNotEqual,
    EmptyGuess,
    EmptyWordle,
    InvalidGuess,
    Ok,
    Last
};

bool initWordsDatabaseFromFile(std::vector<std::string>& db, size_t reserveMemory, const std::string& filename);

void printMenuWithMappedKeys(unsigned char wordOfTheDayKey, unsigned char randomWordKey, unsigned char exitKey);

size_t wordPosOnDayInRange(size_t range);

bool isWordDayPlayed(const std::string& word, const std::string& filename);

bool saveWordDay(const std::string& word, const std::string& filename);

size_t randWordPosInRange(size_t range);

GuessTransformResult transformGuessComparingWordle(std::string& guess, const std::string& wordle, char filler = '*');

} // namespace Wordle
