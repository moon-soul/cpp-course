#include "runaway.hpp"

#include <cstdlib>

#include "munchkin.hpp"
#include "weapon.hpp"

LevelDowngrade::LevelDowngrade(int level) : levelToDowngrade_(level)
{
}

std::string LevelDowngrade::getInfo() const
{
    return "<Munchkin level decreased by (" + std::to_string(levelToDowngrade_) + ")>\n";
}

void LevelDowngrade::apply(Munchkin* munchkin)
{
    munchkin->updateLevelBy(-levelToDowngrade_);
}

LevelDowngradeIf::LevelDowngradeIf(int level, int minimalMunchkinLevel)
    : LevelDowngrade(level),
      minimalMunchkinLevelToApply_(minimalMunchkinLevel)
{
}

std::string LevelDowngradeIf::getInfo() const
{
    return "<If Munchkin {level >= " + std::to_string(minimalMunchkinLevelToApply_) + "}, level decreased by (" + std::to_string(levelToDowngrade_) + ")>\n";
}

void LevelDowngradeIf::apply(Munchkin* munchkin)
{
    if (munchkin->getLevel() >= minimalMunchkinLevelToApply_)
    {
        LevelDowngrade::apply(munchkin);
    }
}

std::string WeaponStrongestRemoval::getInfo() const
{
    return "<Removed (strongest weapon)>\n";
}

void WeaponStrongestRemoval::apply(Munchkin* munchkin)
{
    const size_t munchkinWeaponsSize = munchkin->getWeapons().size();
    if (munchkinWeaponsSize == 0)
    {
        return;
    }
    size_t strongestWeaponPos = 0;
    for (size_t i = 1; i < munchkinWeaponsSize; ++i)
    {
        if (munchkin->getWeapons()[i]->getBasePower() > munchkin->getWeapons()[strongestWeaponPos]->getBasePower())
        {
            strongestWeaponPos = i;
        }
    }
    munchkin->removeWeaponEquipped(strongestWeaponPos);
}

std::string ModifierFromHandRemoval::getInfo() const
{
    return "<Removed (random modifier)>\n";
}

void ModifierFromHandRemoval::apply(Munchkin* munchkin)
{
    const size_t munchkinModifiersSize = munchkin->getModifiers().size();
    if (munchkinModifiersSize == 0)
    {
        return;
    }
    const size_t randomPos = std::rand() % munchkinModifiersSize;
    munchkin->removeModifierFromHand(randomPos);
}
