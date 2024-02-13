#pragma once

#include <memory>
#include <string>

#include "monster_tribe.hpp"

class Weapon
{
public:
    Weapon(const std::string& name, int power);
    virtual ~Weapon() = default;

    virtual int getPower(MonsterTribe monsterTribeModifier) const = 0;
    virtual std::string getInfo() const = 0;

    const std::string& getName() const;
    int getBasePower() const;

protected:
    std::string name_;
    int power_;
};

class CommonWeapon : public Weapon
{
public:
    CommonWeapon(const std::string& name, int power);

    int getPower(MonsterTribe monsterTribeModifier) const override final;
    std::string getInfo() const override final;
};

class UndeadWeapon : public Weapon
{
public:
    UndeadWeapon(const std::string& name, int power);

    int getPower(MonsterTribe monsterTribeModifier) const override final;
    std::string getInfo() const override final;
};

class HolyWeapon : public Weapon
{
public:
    HolyWeapon(const std::string& name, int power);

    int getPower(MonsterTribe monsterTribeModifier) const override final;
    std::string getInfo() const override final;
};

class LegendaryWeapon : public Weapon
{
public:
    LegendaryWeapon(const std::string& name, int power);

    int getPower(MonsterTribe monsterTribeModifier) const override final;
    std::string getInfo() const override final;
};

class UnknownWeapon : public Weapon
{
public:
    UnknownWeapon(const std::string& name, int power);

    int getPower(MonsterTribe monsterTribeModifier) const override final;
    std::string getInfo() const override final;
};

class WeaponDelegator
{
public:
    enum class WeaponType
    {
        Common,
        Undead,
        Holy,
        Legendary,
        Unknown
    };

    std::shared_ptr<Weapon> operator()(const std::string& lineToParse) const;

private:
    inline WeaponDelegator::WeaponType mapStrToType(const std::string& typeName) const;
};
