#include "game.hpp"

#include <cctype>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include "fight.hpp"
#include "modifier.hpp"
#include "monster.hpp"
#include "munchkin.hpp"
#include "defeat.hpp"
#include "utility.hpp"
#include "victory.hpp"
#include "weapon.hpp"

namespace UI
{

void printTextWithDelay(const std::string& text, size_t delay)
{
    std::cout << text << std::flush;
    for (size_t i = 0; i < delay; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << '.' << std::flush;
    }
    std::cout << '\n';
}

void printShuffling()
{
    UI::printTextWithDelay("\nShuffling the deck", 5);
}

void printIntro(Munchkin* munchkin)
{
    std::cout << "Greetings!\n\nEnter Munchkin name: ";
    std::string name;
    std::cin >> name;
    munchkin->setName(name);
    UI::printShuffling();
}

void printWeapons(Munchkin* munchkin)
{
    std::cout << "\n[Inventory]\n";
    const auto& weapons = munchkin->getWeapons();
    for (const auto& weapon : weapons)
    {
        std::cout << '\n' << weapon->getInfo();
    }
}

void printModifiers(Munchkin* munchkin)
{
    std::cout << "\n[Modifiers]\n";
    const auto& modifiers = munchkin->getModifiers();
    const size_t modifiersSize = modifiers.size();
    for (size_t i = 0; i < modifiersSize; ++i)
    {
        std::cout << "\n[" << i << "] " << modifiers[i]->getInfo();
    }
}

void printPlayerDeck(Munchkin* munchkin)
{
    std::cout << "\nMunchkin [" << munchkin->getName() << "]\nLevel: (" << munchkin->getLevel() << ")\n";
    UI::printTextWithDelay("\nOpening inventory", 3);
    UI::printWeapons(munchkin);
    UI::printTextWithDelay("\nGetting modifiers", 3);
    UI::printModifiers(munchkin);
}

void enterAnyKeyToContinue()
{
    std::cout << "\nEnter any key to continue...\n> ";
    char key;
    std::cin >> key;
}

void printMonsterSelection()
{
    UI::printTextWithDelay("\nSelecting monster card", 5);
}

void printMonsterInfo(const std::shared_ptr<Monster>& monster)
{
    std::cout << "\n[" << monster->getName() << "]\nLevel: (" << monster->getLevel() << ")\nTribe: {" << Helpers::mapMonsterTribeToStr(monster->getTribe()) << "}\n";
}

void printMunchkinPower(Munchkin* munchkin, Fight* fight)
{
    std::cout << "\nMunchkin [" << munchkin->getName() << "]\nPower: (" << fight->getMunchkinPower() << ")\n";
}

void printMonsterPower(const std::shared_ptr<Monster>& monster, Fight* fight)
{
    std::cout << "\nMonster [" << monster->getName() << "]\nPower: (" << fight->getMonsterPower() << ")\n";
}

void printMunchkinWonRound(Munchkin* munchkin, const std::shared_ptr<Monster>& monster)
{
    std::cout << "\nCongratulations! Munchkin [" << munchkin->getName() << "] has just won the round!"
              << "\nPositive effect: " << monster->getVictoryPolicy()->getInfo();
}

void printCurrentFightResult(int powerDifference)
{
    std::cout << "\nToo weak! Missing (" << std::abs(powerDifference - 1) << ") power!\n";
}

enum class UserInput
{
    ApplyModifier,
    Runaway,
    None
};

UserInput readUserBehavior()
{
    std::cout << "\nUse card from the hand or try to runaway? (C/R): ";
    char choice;
    std::cin >> choice;
    choice = std::toupper(choice);
    switch (choice)
    {
    case 'C': return UI::UserInput::ApplyModifier;
    case 'R': return UI::UserInput::Runaway;
    default: return UI::UserInput::None;
    }
}

void printDiceRoll()
{
    UI::printTextWithDelay("\nRolling the dice", 5);
}

void printDiceRollResult(int roll)
{
    std::cout << "\n(" << roll << ") on the dice!\n";
}

void printMunchkinRunaway(Munchkin* munchkin, const std::shared_ptr<Monster>& monster)
{
    std::cout << "\nMunchkin [" << munchkin->getName() << "] has just managed to runaway from [" << monster->getName() << "]\n";
}

void printMunchkinLost(Munchkin* munchkin, const std::shared_ptr<Monster>& monster)
{
    std::cout << "\nMunchkin [" << munchkin->getName() << "] has just lost the game to [" << monster->getName() << "]"
              << "\nNegative effect: " << monster->getDefeatPolicy()->getInfo();
}

int selectModifierFromHand(int handSize)
{
    std::cout << "\nSelect card from the hand: ";
    int choice;
    std::cin >> choice;
    if (choice < 0 or choice >= handSize)
    {
        choice = -1;
    }
    return choice;
}

void printMunchkinWonGame(Munchkin* munchkin)
{
    std::cout << "\nCongratulations! Munchkin [" << munchkin->getName() << "] has just won the game!\n";
}

} // namespace UI

Game::Game(const std::string& munchkinName,
           const std::string& weaponsFilePath,
           const std::string& modifiersFilePath,
           const std::string& monstersFilePath)
    : munchkin_(munchkinName),
      weaponsDeck_(weaponsFilePath, WeaponDelegator{}),
      modifiersDeck_(modifiersFilePath, ModifierDelegator{}),
      monstersDeck_(monstersFilePath, MonsterDelegator{})
{
    defeatPolicies_.reserve(4);
    defeatPolicies_.emplace_back(new LevelDowngrade(2));
    defeatPolicies_.emplace_back(new LevelDowngradeIf(3, 5));
    defeatPolicies_.emplace_back(new WeaponStrongestRemoval());
    defeatPolicies_.emplace_back(new ModifierFromHandRemoval());
    victoryPolicies_.reserve(4);
    victoryPolicies_.emplace_back(new LevelIncrease(2));
    victoryPolicies_.emplace_back(new LevelIncrease(4));
    victoryPolicies_.emplace_back(new GetNewWeapon(&weaponsDeck_));
    victoryPolicies_.emplace_back(new GetNewModifier(&modifiersDeck_));
}

Game::~Game()
{
    for (Defeat* policy : defeatPolicies_)
    {
        delete policy;
    }
    for (Victory* policy : victoryPolicies_)
    {
        delete policy;
    }
}

void Game::run()
{
    std::srand(std::time(0));
    UI::printIntro(&munchkin_);
    generateMunchkinInitialCards(Constants::INITIAL_WEAPONS, Constants::INITIAL_MODIFIERS);
    while (munchkin_.getLevel() < Constants::WINNING_LEVEL)
    {
        UI::printPlayerDeck(&munchkin_);
        UI::enterAnyKeyToContinue();
        UI::printMonsterSelection();
        const auto& monster = generateMonsterWithRandomPolicies();
        UI::printMonsterInfo(monster);
        Fight fight;
        fight.setMunchkin(&munchkin_);
        fight.setMonster(monster);
        fight.start();
        while (not fight.getFinish())
        {
            const int munchkinMonsterDifference = fight.getMunchkinMonsterPowerDifference();
            UI::printMunchkinPower(&munchkin_, &fight);
            UI::printMonsterPower(monster, &fight);
            if (munchkinMonsterDifference > 0)
            {
                fight.victoryFlow();
                UI::printMunchkinWonRound(&munchkin_, monster);
                UI::enterAnyKeyToContinue();
            }
            else
            {
                UI::printCurrentFightResult(munchkinMonsterDifference);
                const UI::UserInput input = UI::readUserBehavior();
                if (input == UI::UserInput::Runaway)
                {
                    UI::printDiceRoll();
                    const int roll = fight.diceRoll();
                    UI::printDiceRollResult(roll);
                    if (roll >= 5)
                    {
                        fight.runawayFlow();
                        UI::printMunchkinRunaway(&munchkin_, monster);
                    }
                    else
                    {
                        fight.defeatFlow();
                        UI::printMunchkinLost(&munchkin_, monster);
                    }
                    UI::enterAnyKeyToContinue();
                }
                else if (input == UI::UserInput::ApplyModifier)
                {
                    UI::printTextWithDelay("\nGetting modifiers", 2);
                    UI::printModifiers(&munchkin_);
                    const int choice = UI::selectModifierFromHand(static_cast<int>(munchkin_.getModifiers().size()));
                    if (choice != -1)
                    {
                        fight.applyModifier(choice);
                    }
                }
            }
        }
    }
    UI::printMunchkinWonGame(&munchkin_);
}

void Game::generateMunchkinInitialCards(size_t initialWeapons, size_t initialModifiers)
{
    for (size_t i = 0; i < initialWeapons; ++i)
    {
        munchkin_.addWeapon(weaponsDeck_.getUniqueEntry());
    }
    for (size_t i = 0; i < initialModifiers; ++i)
    {
        munchkin_.addModifier(modifiersDeck_.getUniqueEntry());
    }
}

const std::shared_ptr<Monster> Game::generateMonsterWithRandomPolicies()
{
    const size_t randomDefeatPos = std::rand() % defeatPolicies_.size();
    const size_t randomVictoryPos = std::rand() % victoryPolicies_.size();
    const auto monster = monstersDeck_.getUniqueEntry();
    monster->setDefeatPolicy(defeatPolicies_[randomDefeatPos]);
    monster->setVictoryPolicy(victoryPolicies_[randomVictoryPos]);
    return monster;
}
