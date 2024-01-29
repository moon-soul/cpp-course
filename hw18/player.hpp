#pragma once

#include <string>

#include "weapon.hpp"
#include "player_class.hpp"

class Player
{
public:
    Player(const std::string& name = "<blank>",
           Weapon* weapon = new BareHand,
           PlayerClass* playerClass = new DefaultClass);
    ~Player();

    std::string getName() const;
    std::string getCurrentWeaponName() const;
    int getHealthpoints() const;
    int getBaseDamage(size_t distance) const;
    float getClassAttackBonus() const;
    float getClassDefenseBonus() const;
    float getClassMissChance() const;
    bool isEliminated() const;

    void setWeapon(Weapon* weapon);
    void setPlayerClass(PlayerClass* playerClass);

    void attack(Player& attacked, size_t distance);

private:
    void setHealthpoints(int healthpoints);

    int healthpoints_ = 100;
    std::string name_;

    Weapon* weapon_;
    PlayerClass* playerClass_;
};
