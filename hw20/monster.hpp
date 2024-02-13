#pragma once

#include <memory>
#include <string>

#include "monster_tribe.hpp"

class Runaway;
class Victory;

class Monster
{
public:
    Monster(const std::string& name, int level, MonsterTribe tribe);

    const std::string& getName() const;
    int getLevel() const;
    MonsterTribe getTribe() const;
    Runaway* getRunawayPolicy() const;
    Victory* getVictoryPolicy() const;

    void setRunawayPolicy(Runaway* runawayPolicy);
    void setVictoryPolicy(Victory* victoryPolicy);

private:
    std::string name_;
    int level_;
    MonsterTribe tribe_;
    Runaway* runawayPolicy_ = nullptr;
    Victory* victoryPolicy_ = nullptr;
};

class MonsterDelegator
{
public:
    std::shared_ptr<Monster> operator()(const std::string& lineToParse) const;
};
