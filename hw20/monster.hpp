#pragma once

#include <memory>
#include <string>

#include "monster_tribe.hpp"

class Defeat;
class Victory;

class Monster
{
public:
    Monster(const std::string& name, int level, MonsterTribe tribe);

    const std::string& getName() const;
    int getLevel() const;
    MonsterTribe getTribe() const;
    Defeat* getDefeatPolicy() const;
    Victory* getVictoryPolicy() const;

    void setDefeatPolicy(Defeat* defeatPolicy);
    void setVictoryPolicy(Victory* victoryPolicy);

private:
    std::string name_;
    int level_;
    MonsterTribe tribe_;
    Defeat* defeatPolicy_ = nullptr;
    Victory* victoryPolicy_ = nullptr;
};

class MonsterDelegator
{
public:
    std::shared_ptr<Monster> operator()(const std::string& lineToParse) const;
};
