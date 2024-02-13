#include "fight.hpp"

#include <cstdlib>

#include "modifier.hpp"
#include "monster.hpp"
#include "munchkin.hpp"
#include "runaway.hpp"
#include "victory.hpp"
#include "weapon.hpp"

int Fight::getMunchkinPower() const
{
    return munchkinPower_;
}

int Fight::getMonsterPower() const
{
    return monsterPower_;
}

int Fight::getMunchkinMonsterPowerDifference() const
{
    return munchkinPower_ - monsterPower_;
}

bool Fight::getFinish() const
{
    return result_ != Fight::Result::InProgress;
}

int Fight::diceRoll() const
{
    return (std::rand() % 6) + 1;
}

void Fight::setMunchkin(Munchkin* munchkin)
{
    munchkin_ = munchkin;
}

void Fight::setMonster(const std::shared_ptr<Monster>& monster)
{
    monster_ = monster;
}

void Fight::start()
{
    result_ = Fight::Result::InProgress;
    calculateMunchkinPower();
    calculateMonsterPower();
}

void Fight::victoryFlow()
{
    munchkin_->updateLevelBy(1);
    Victory* policy = monster_->getVictoryPolicy();
    if (policy != nullptr)
    {
        policy->apply(munchkin_);
    }
    result_ = Fight::Result::MunchkinWon;
}

void Fight::runawayFlow()
{
    result_ = Fight::Result::MunchkinRunaway;
}

void Fight::defeatFlow()
{
    Runaway* policy = monster_->getRunawayPolicy();
    if (policy != nullptr)
    {
        policy->apply(munchkin_);
    }
    result_ = Fight::Result::MonsterWon;
}

void Fight::applyModifier(int choice)
{
    const auto modifier = munchkin_->popModifier(choice);
    modifier->apply(munchkin_, monster_);
    munchkinPower_ += modifier->getMunchkinModifier();
    monsterPower_ += modifier->getMonsterModifier();
}

void Fight::calculateMunchkinPower()
{
    munchkinPower_ += munchkin_->getLevel();
    for (const auto& weapon : munchkin_->getWeapons())
    {
        munchkinPower_ += weapon->getPower(monster_->getTribe());
    }
}

void Fight::calculateMonsterPower()
{
    monsterPower_ = monster_->getLevel();
}
