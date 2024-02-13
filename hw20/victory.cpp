#include "victory.hpp"

#include "munchkin.hpp"

Victory::Victory(Deck<Weapon>* weaponsDeck) : weaponsDeck_(weaponsDeck)
{
}

Victory::Victory(Deck<Modifier>* modifiersDeck) : modifiersDeck_(modifiersDeck)
{
}

LevelIncrease::LevelIncrease(int level) : levelToIncrease_(level)
{
}

std::string LevelIncrease::getInfo() const
{
    return "<Munchkin level increased by (" + std::to_string(levelToIncrease_) + ")>\n";
}

void LevelIncrease::apply(Munchkin* munchkin)
{
    munchkin->updateLevelBy(levelToIncrease_);
}

GetNewWeapon::GetNewWeapon(Deck<Weapon>* weaponsDeck) : Victory(weaponsDeck)
{
}

std::string GetNewWeapon::getInfo() const
{
    return "<Got (new weapon) from the deck>\n";
}

void GetNewWeapon::apply(Munchkin* munchkin)
{
    if (weaponsDeck_ != nullptr)
    {
        munchkin->addWeapon(weaponsDeck_->getUniqueEntry());
    }
}

GetNewModifier::GetNewModifier(Deck<Modifier>* modifiersDeck) : Victory(modifiersDeck)
{
}

std::string GetNewModifier::getInfo() const
{
    return "<Got (new modifier) from the deck>\n";
}

void GetNewModifier::apply(Munchkin* munchkin)
{
    if (modifiersDeck_ != nullptr)
    {
        munchkin->addModifier(modifiersDeck_->getUniqueEntry());
    }
}
