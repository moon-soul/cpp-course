#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "deck.hpp"
#include "munchkin.hpp"

class Weapon;
class Modifier;
class Monster;
class Runaway;
class Victory;

class Game
{
public:
    Game(const std::string& munchkinName,
         const std::string& weaponsFilePath,
         const std::string& modifiersFilePath,
         const std::string& monstersFilePath);
    ~Game();

    void run();

private:
    void generateMunchkinInitialCards(size_t initialWeapons, size_t initialModifiers);
    const std::shared_ptr<Monster>& generateMonsterWithRandomPolicies();

    Munchkin munchkin_;
    Deck<Weapon> weaponsDeck_;
    Deck<Modifier> modifiersDeck_;
    Deck<Monster> monstersDeck_;
    std::vector<Runaway*> runawayPolicies_;
    std::vector<Victory*> victoryPolicies_;
};
