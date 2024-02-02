# Wordle

## Introduction
The project presents a console-based version of the popular Wordle game, enabling players to guess words based on feedback from their previous guesses. It is designed with modularity and simplicity in mind, leveraging C++ for its implementation.

## Functionality
The codebase is structured around several key components:

- **Word Database Initialization**: Utilizes a file containing a list of words (`words.txt`) to populate the game's word database, ensuring a diverse set of challenges. This database can be enhanced by adding additional words to `words.txt`.
- **Game Logic**: Facilitates the core gameplay loop, including word selection (either "Word of the Day" or a random word), player input handling, and guess evaluation.
- **User Interface**: Displays a simple console-based menu, allowing players to interact with the game through specific action keys.
- **Guess Transformation**: Compares the player's guess to the target word, providing feedback on the accuracy of each letter.

### Detailed Analysis
- `namespace Wordle`: Encapsulates all game-related functionality, preventing naming conflicts and enhancing code readability.
- `enum class GuessTransformResult`: Defines potential outcomes of a guess comparison, aiding in the flow control during guess evaluation.

Detailed functionality provided within the `Wordle` namespace includes:

- `initWordsDatabaseFromFile`: Reads words from a file and stores them in a vector, converting them to uppercase for consistency.
- `printMenuWithMappedKeys`: Displays the game menu and maps specific actions to user-defined keys for intuitive interaction.
- `wordPosOnDayInRange`: Determines the position of the word of the day within a given range, supporting the "Word of the Day" feature.
- `isWordDayPlayed`: Verifies if the "Word of the Day" has been played, preventing replay of the same word.
- `saveWordDay`: Saves the "Word of the Day" to track played words, ensuring the uniqueness of daily challenges.
- `randWordPosInRange`: Selects a random word position within a specified range, adding variety to the word selection process.
- `transformGuessComparingWordle`: Transforms the player's guess by comparing it with the actual word, marking correct and incorrect letters.

## User Interaction
Players can interact with the game through a series of action keys, which are defined and can be rebinded within `main.cpp`. The default keys are:

- `1`: Select the "Word of the Day".
- `2`: Choose a random word.
- `q`: Exit the game.

## Compilation and Testing
The project was compiled and tested using the following command:
```
clang++ -std=c++20 -Wall -Wextra -pedantic *.cpp
```
This ensures strict adherence to modern C++ standards and practices, enhancing the code quality and reliability.

## Conclusion
The project is a concise and efficient implementation of the Wordle game, designed to provide an engaging and educational experience to users. By offering insights into basic game development concepts such as file handling, user input processing, and feedback generation, it serves as an excellent reference for enthusiasts looking to delve into game programming with C++.
