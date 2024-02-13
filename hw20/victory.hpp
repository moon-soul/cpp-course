#pragma once

#include <string>

#include "deck.hpp"

class Weapon;
class Modifier;
class Munchkin;

class Victory
{
public:
    Victory() = default;
    Victory(Deck<Weapon>* weaponsDeck);
    Victory(Deck<Modifier>* modifiersDeck);
    virtual ~Victory() = default;

    virtual std::string getInfo() const = 0;
    virtual void apply(Munchkin* munchkin) = 0;

protected:
    Deck<Weapon>* weaponsDeck_ = nullptr;
    Deck<Modifier>* modifiersDeck_ = nullptr;
};

class LevelIncrease : public Victory
{
public:
    LevelIncrease(int level = 1);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin) override final;

private:
    int levelToIncrease_;
};

class GetNewWeapon : public Victory
{
public:
    GetNewWeapon(Deck<Weapon>* weaponsDeck);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin) override final;
};

class GetNewModifier : public Victory
{
public:
    GetNewModifier(Deck<Modifier>* modifiersDeck);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin) override final;
};
