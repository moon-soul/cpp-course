#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "wordle.hpp"

int main()
{
    /* File config */
    const std::string storageFile{"words.txt"};
    const std::string saveFile{".wotd"};

    /* Setup keys */
    constexpr unsigned char wordOfTheDayKey = '1';
    constexpr unsigned char randomWordKey = '2';
    constexpr unsigned char exitKey = 'q';

    /* Init words database */
    std::vector<std::string> wordsDatabase;
    constexpr size_t reserveMemory = 100;
    if (not Wordle::initWordsDatabaseFromFile(wordsDatabase, reserveMemory, storageFile))
    {
        std::cout << "Unable to init words database from file \"" << storageFile << "\"\n";
        return -1;
    }
    std::cout << "Successful init of words database from file \"" << storageFile << "\"\n";

    std::srand(std::time(0));

    /* Game loop */
    while (true)
    {
        Wordle::printMenuWithMappedKeys(wordOfTheDayKey, randomWordKey, exitKey);
        std::string wordle;
        bool toSave = false;
        unsigned char choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case wordOfTheDayKey:
            wordle = wordsDatabase[Wordle::wordPosOnDayInRange(wordsDatabase.size())];
            if (Wordle::isWordDayPlayed(wordle, saveFile))
            {
                std::cout << "\nWord of the Day has been already played! Come back tomorrow.\n";
                continue;
            }
            toSave = true;
            break;
        case randomWordKey:
            wordle = wordsDatabase[Wordle::randWordPosInRange(wordsDatabase.size())];
            break;
        case exitKey:
            std::cout << "\nExiting...\n";
            return 0;
        default:
            std::cout << "\nWrong input. Try again.\n";
            continue;
        }
        std::cout << "\nWordle has (" << wordle.length() << ") letters.\n";
        size_t tries = 0;
        std::string guess;
        while (guess != wordle)
        {
            std::cout << "\nGuess:  ";
            std::cin >> guess;
            const Wordle::GuessTransformResult result = Wordle::transformGuessComparingWordle(guess, wordle);
            std::cout << "Result: ";
            switch (result)
            {
            case Wordle::GuessTransformResult::Ok:
                std::cout << guess;
                ++tries;
                break;
            case Wordle::GuessTransformResult::LengthNotEqual:
                std::cout << "Length not equal!";
                break;
            case Wordle::GuessTransformResult::EmptyGuess:
                std::cout << "Empty guess!";
                break;
            case Wordle::GuessTransformResult::EmptyWordle:
                std::cout << "Empty wordle!";
                break;
            case Wordle::GuessTransformResult::InvalidGuess:
                std::cout << "Invalid guess!";
                break;
            default:
                std::cout << "Unknown error!";
                break;
            }
        }
        std::cout << "\n\nCorrect! The Wordle was [" << wordle << ']'
                  << "\nIt took (" << tries << ") tries to find out."
                  << '\n';
        if (not toSave)
        {
            continue;
        }
        else if (not Wordle::saveWordDay(wordle, saveFile))
        {
            std::cout << "\nUnable to save Word of the Day to file \"" << saveFile << "\"\n";
            return -1;
        }
    }
}
