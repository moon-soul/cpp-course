#include "weapon.hpp"

#include <cassert>
#include <sstream>
#include <vector>

#include "utility.hpp"

Weapon::Weapon(const std::string& name, int power) : name_(name), power_(power)
{
}

const std::string& Weapon::getName() const
{
    return name_;
}

int Weapon::getBasePower() const
{
    return power_;
}

CommonWeapon::CommonWeapon(const std::string& name, int power) : Weapon(name, power)
{
}

int CommonWeapon::getPower(MonsterTribe monsterTribeModifier) const
{
    switch (monsterTribeModifier)
    {
    case MonsterTribe::Human:
    case MonsterTribe::Undead:
    case MonsterTribe::Zombie:
    case MonsterTribe::God:
    default: return getBasePower();
    }
}

std::string CommonWeapon::getInfo() const
{
    return "<" + Constants::WeaponTypeName::COMMON + "> \"" + getName() + "\"\nPower: (" + std::to_string(getBasePower()) + ")\nPerk: none\n";
}

UndeadWeapon::UndeadWeapon(const std::string& name, int power) : Weapon(name, power)
{
}

int UndeadWeapon::getPower(MonsterTribe monsterTribeModifier) const
{
    switch (monsterTribeModifier)
    {
    case MonsterTribe::Undead: return getBasePower() * 2;
    case MonsterTribe::Human:
    case MonsterTribe::Zombie:
    case MonsterTribe::God:
    default: return getBasePower();
    }
}

std::string UndeadWeapon::getInfo() const
{
    return "<" + Constants::WeaponTypeName::UNDEAD + "> \"" + getName() + "\"\nPower: (" + std::to_string(getBasePower()) + ")\nPerk: (x2) vs {UNDEAD}\n";
}

HolyWeapon::HolyWeapon(const std::string& name, int power) : Weapon(name, power)
{
}

int HolyWeapon::getPower(MonsterTribe monsterTribeModifier) const
{
    switch (monsterTribeModifier)
    {
    case MonsterTribe::God: return getBasePower() * 2;
    case MonsterTribe::Human:
    case MonsterTribe::Undead:
    case MonsterTribe::Zombie:
    default: return getBasePower();
    }
}

std::string HolyWeapon::getInfo() const
{
    return "<" + Constants::WeaponTypeName::HOLY + "> \"" + getName() + "\"\nPower: (" + std::to_string(getBasePower()) + ")\nPerk: (x2) vs {GOD}\n";
}

LegendaryWeapon::LegendaryWeapon(const std::string& name, int power) : Weapon(name, power)
{
}

int LegendaryWeapon::getPower(MonsterTribe monsterTribeModifier) const
{
    switch (monsterTribeModifier)
    {
    case MonsterTribe::Human:
    case MonsterTribe::Undead:
    case MonsterTribe::Zombie:
    case MonsterTribe::God:
    default: return getBasePower() * 2;
    }
}

std::string LegendaryWeapon::getInfo() const
{
    return "<" + Constants::WeaponTypeName::LEGENDARY + "> \"" + getName() + "\"\nPower: (" + std::to_string(getBasePower()) + ")\nPerk: (x2) vs {ALL}\n";
}

UnknownWeapon::UnknownWeapon(const std::string& name, int power) : Weapon(name, power)
{
}

int UnknownWeapon::getPower(MonsterTribe monsterTribeModifier) const
{
    switch (monsterTribeModifier)
    {
    case MonsterTribe::Human:
    case MonsterTribe::Undead:
    case MonsterTribe::Zombie:
    case MonsterTribe::God:
    default: return getBasePower() * 0;
    }
}

std::string UnknownWeapon::getInfo() const
{
    return "<" + Constants::WeaponTypeName::UNKNOWN + "> \"" + getName() + "\"\nPower: (" + std::to_string(getBasePower()) + ")\nPerk: doesn't hurt\n";
}

std::shared_ptr<Weapon> WeaponDelegator::operator()(const std::string& lineToParse) const
{
    assert(not lineToParse.empty());
    constexpr size_t weaponTokens = 3;
    std::vector<std::string> tokens;
    tokens.reserve(weaponTokens);
    std::istringstream iss(lineToParse);
    std::string buffStr;
    while (std::getline(iss, buffStr, ';'))
    {
        tokens.emplace_back(buffStr);
    }
    const std::string typeName = tokens[0];
    const std::string name = tokens[1];
    const int power = std::stoi(tokens[2]);
    const WeaponDelegator::WeaponType type = mapStrToType(typeName);
    switch (type)
    {
    case WeaponDelegator::WeaponType::Common: return std::make_shared<CommonWeapon>(name, power);
    case WeaponDelegator::WeaponType::Undead: return std::make_shared<UndeadWeapon>(name, power);
    case WeaponDelegator::WeaponType::Holy: return std::make_shared<HolyWeapon>(name, power);
    case WeaponDelegator::WeaponType::Legendary: return std::make_shared<LegendaryWeapon>(name, power);
    case WeaponDelegator::WeaponType::Unknown: return std::make_shared<UnknownWeapon>(name, power);
    }
}

inline WeaponDelegator::WeaponType WeaponDelegator::mapStrToType(const std::string& typeName) const
{
    if (typeName == Constants::WeaponTypeName::COMMON) return WeaponDelegator::WeaponType::Common;
    if (typeName == Constants::WeaponTypeName::UNDEAD) return WeaponDelegator::WeaponType::Undead;
    if (typeName == Constants::WeaponTypeName::HOLY) return WeaponDelegator::WeaponType::Holy;
    if (typeName == Constants::WeaponTypeName::LEGENDARY) return WeaponDelegator::WeaponType::Legendary;
    return WeaponDelegator::WeaponType::Unknown;
}
