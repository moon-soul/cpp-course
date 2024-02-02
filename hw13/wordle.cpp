#include "wordle.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

bool Wordle::initWordsDatabaseFromFile(std::vector<std::string>& db, size_t reserveMemory, const std::string& filename)
{
    if (filename.empty())
    {
        return false;
    }
    std::ifstream storageFile(filename);
    if (!storageFile.is_open())
    {
        return false;
    }
    db.reserve(reserveMemory);
    std::string buffStr;
    while (std::getline(storageFile, buffStr))
    {
        std::transform(buffStr.begin(), buffStr.end(), buffStr.begin(), ::toupper);
        db.emplace_back(buffStr);
    }
    storageFile.close();
    return true;
}

void Wordle::printMenuWithMappedKeys(unsigned char wordOfTheDayKey, unsigned char randomWordKey, unsigned char exitKey)
{
    std::cout << "\nWordle\n"
              << wordOfTheDayKey << " - Word of the Day\n"
              << randomWordKey << " - Random Word\n"
              << exitKey << " - Exit\n";
}

size_t Wordle::wordPosOnDayInRange(size_t range)
{
    const std::time_t currentTime = std::time(0);
    const std::tm* const ltm = std::localtime(&currentTime);
    return ltm->tm_yday % range;
}

bool Wordle::isWordDayPlayed(const std::string& word, const std::string& filename)
{
    assert(!filename.empty());
    std::ifstream wordDayFile(filename);
    if (!wordDayFile.is_open())
    {
        return false;
    }
    std::string buffStr;
    wordDayFile >> buffStr; // Save file will always contain only one word
    wordDayFile.close();
    if (buffStr == word)
    {
        return true;
    }
    return false;
}

bool Wordle::saveWordDay(const std::string& word, const std::string& filename)
{
    if (filename.empty())
    {
        return false;
    }
    std::ofstream saveFile(filename);
    if (!saveFile.is_open())
    {
        return false;
    }
    saveFile << word << '\n'; // Save file will always contain only one word
    saveFile.close();
    return true;
}

size_t Wordle::randWordPosInRange(size_t range)
{
    std::srand(std::time(0));
    return std::rand() % range; // [0; range)
}

Wordle::GuessTransformResult Wordle::transformGuessComparingWordle(std::string& guess, const std::string& wordle, char filler)
{
    const size_t guessLength = guess.length();
    const size_t wordleLength = wordle.length();

    if (guessLength != wordleLength)
    {
        return GuessTransformResult::LengthNotEqual;
    }
    if (guess.empty())
    {
        return GuessTransformResult::EmptyGuess;
    }
    if (wordle.empty())
    {
        return GuessTransformResult::EmptyWordle;
    }

    /* In case lowercase guess */
    for (char& c : guess)
    {
        if (!std::isalpha(c))
        {
            return GuessTransformResult::InvalidGuess;
        }
        c = std::toupper(c);
    }

    constexpr uint16_t lettersInAlphabet = 26;
    size_t startingSearchPosForChar[lettersInAlphabet] = {0}; // Will contain only uppercase alphabet

    for (size_t i = 0; i < guessLength; ++i)
    {
        if (guess[i] == wordle[i])
        {
            continue;
        }

        size_t foundPos = std::string::npos;
        const size_t startPos = startingSearchPosForChar[guess[i] - 'A'];
        for (size_t j = startPos; j < wordleLength; ++j)
        {
            if (guess[i] == wordle[j])
            {
                foundPos = j;
                startingSearchPosForChar[guess[i] - 'A'] = j + 1;
                break;
            }
        }

        if (foundPos == std::string::npos)
        {
            guess[i] = filler;

            /* Not to search for the same missing character again */
            startingSearchPosForChar[guess[i] - 'A'] = std::string::npos;
        }
        else if (guess[foundPos] == wordle[foundPos])
        {
            --i;
        }
        else
        {
            guess[i] = std::tolower(guess[i]);
        }
    }
    return GuessTransformResult::Ok;
}
