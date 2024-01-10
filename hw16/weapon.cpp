#include "weapon.hpp"

#include <iostream>

Weapon::Weapon(const char* name, uint16_t damage, uint16_t range)
    : name_(name), damage_(damage), range_(range)
{
}

std::string Weapon::getName() const
{
    return name_;
}

void Weapon::printInfo() const
{
    std::cout << "\nWeapon [" << name_ << ']'
              << "\nDamage: " << damage_
              << "\nRange: " << range_
              << '\n';
}
