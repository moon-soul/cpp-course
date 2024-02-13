#include "munchkin.hpp"

#include <cassert>

Munchkin::Munchkin(const std::string& name) : name_(name)
{
}

const std::string& Munchkin::getName() const
{
    return name_;
}

int Munchkin::getLevel() const
{
    return level_;
}

const std::vector<std::shared_ptr<Weapon>>& Munchkin::getWeapons() const
{
    return weapons_;
}

const std::vector<std::shared_ptr<Modifier>>& Munchkin::getModifiers() const
{
    return modifiers_;
}

void Munchkin::setName(const std::string& name)
{
    if (name.empty())
    {
        return;
    }
    name_ = name;
}

void Munchkin::updateLevelBy(int levels)
{
    if (level_ + levels <= 0)
    {
        level_ = 1;
    }
    else
    {
        level_ += levels;
    }
}

void Munchkin::addWeapon(const std::shared_ptr<Weapon>& weapon)
{
    weapons_.emplace_back(weapon);
}

void Munchkin::addModifier(const std::shared_ptr<Modifier>& modifier)
{
    modifiers_.emplace_back(modifier);
}

std::shared_ptr<Modifier> Munchkin::popModifier(int pos)
{
    assert(pos >= 0 and pos < static_cast<int>(modifiers_.size()));
    const auto modifier = modifiers_[pos];
    modifiers_.erase(modifiers_.begin() + pos);
    return modifier;
}

void Munchkin::removeWeaponEquipped(size_t pos)
{
    assert(pos >= 0 and pos < weapons_.size());
    weapons_.erase(weapons_.begin() + pos);
}

void Munchkin::removeModifierFromHand(size_t pos)
{
    assert(pos >= 0 and pos < modifiers_.size());
    modifiers_.erase(modifiers_.begin() + pos);
}
