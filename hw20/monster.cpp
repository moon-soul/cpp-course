#include "monster.hpp"

#include <cassert>
#include <sstream>
#include <vector>

#include "utility.hpp"

Monster::Monster(const std::string& name, int level, MonsterTribe tribe)
    : name_(name), level_(level), tribe_(tribe)
{
}

const std::string& Monster::getName() const
{
    return name_;
}

int Monster::getLevel() const
{
    return level_;
}

MonsterTribe Monster::getTribe() const
{
    return tribe_;
}

Runaway* Monster::getRunawayPolicy() const
{
    return runawayPolicy_;
}

Victory* Monster::getVictoryPolicy() const
{
    return victoryPolicy_;
}

void Monster::setRunawayPolicy(Runaway* runawayPolicy)
{
    runawayPolicy_ = runawayPolicy;
}

void Monster::setVictoryPolicy(Victory* victoryPolicy)
{
    victoryPolicy_ = victoryPolicy;
}

std::shared_ptr<Monster> MonsterDelegator::operator()(const std::string& lineToParse) const
{
    assert(not lineToParse.empty());
    constexpr size_t monsterTokens = 3;
    std::vector<std::string> tokens;
    tokens.reserve(monsterTokens);
    std::istringstream iss(lineToParse);
    std::string buffStr;
    while (std::getline(iss, buffStr, ';'))
    {
        tokens.emplace_back(buffStr);
    }
    const std::string name = tokens[0];
    const int level = std::stoi(tokens[1]);
    const std::string tribeName = tokens[2];
    return std::make_shared<Monster>(name, level, Helpers::mapStrToMonsterTribe(tribeName));
}
