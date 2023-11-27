#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

int generateRandomNumber(int range)
{
    std::cout << "\nGenerating random number [0, " << range << "]...\n";
    std::srand(std::time(nullptr));
    return std::rand() % (range + 1);
}

int main()
{
    int highscore = std::numeric_limits<int>::max();
    int range = 50;
    int tries = 0;
    int guess = 0;
    int diff = 0;

    int generated = generateRandomNumber(range);

    while (true)
    {
        std::cout << "\nEnter your guess (-1 to quit): ";
        std::cin >> guess;

        if (guess == -1)
        {
            std::cout << "\nExiting...\n";
            break;
        }
        if (guess > range || guess < -1)
        {
            std::cout << "\nInvalid guess: " << guess << " is out of allowed range. Try again.\n";
            continue;
        }

        ++tries;
        diff = guess - generated;

        if (diff == 0)
        {
            highscore = tries > highscore ? highscore : tries;
            std::cout << "\nCongratulations! " << guess << " is the correct answer!"
                         "\nIt took " << tries << " tries to find out."
                         "\nHighest score is " << highscore << " tries.\n";

            generated = generateRandomNumber(range);
            tries = 0;
            continue;
        }
        else if (diff >= 20)
        {
            std::cout << "\nYou guessed quite a lot more.";
        }
        else if (diff >= 10)
        {
            std::cout << "\nYou guessed quite a bit more.";
        }
        else if (diff > -10)
        {
            std::cout << "\nAlmost, but not quite.";
        }
        else if (diff <= -20)
        {
            std::cout << "\nYou guessed quite a lot less.";
        }
        else if (diff <= -10)
        {
            std::cout << "\nYou guessed quite a bit less.";
        }
        std::cout << " Try again.\n";
    }
    return 0;
}
