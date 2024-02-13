#pragma once

#include <memory>

class Munchkin;
class Monster;

class Fight
{
public:
    enum class Result
    {
        NotStarted,
        InProgress,
        MunchkinWon,
        MunchkinRunaway,
        MonsterWon
    };

    int getMunchkinPower() const;
    int getMonsterPower() const;
    int getMunchkinMonsterPowerDifference() const;
    bool getFinish() const;
    int diceRoll() const;

    void setMunchkin(Munchkin* munchkin);
    void setMonster(const std::shared_ptr<Monster>& monster);
    void start();
    void victoryFlow();
    void runawayFlow();
    void defeatFlow();
    void applyModifier(int choice);

private:
    void calculateMunchkinPower();
    void calculateMonsterPower();

    int munchkinPower_ = 0;
    int monsterPower_ = 0;
    Munchkin* munchkin_;
    std::shared_ptr<Monster> monster_;
    Fight::Result result_ = Fight::Result::NotStarted;
};
