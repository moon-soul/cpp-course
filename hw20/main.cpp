#include "game.hpp"
#include "utility.hpp"

int main()
{
    Game game(Constants::DEFAULT_MUNCHKIN_NAME,
              Constants::FilePath::WEAPONS_FILE_PATH,
              Constants::FilePath::MODIFIERS_FILE_PATH,
              Constants::FilePath::MONSTERS_FILE_PATH);
    game.run();
    return 0;
}
