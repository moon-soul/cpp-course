#pragma once

#include "class_name.hpp"
#include "team.hpp"
#include "weapon.hpp"

class Team;

class Player
{
public:
    Player(const char* name, ClassName className, Weapon* weapon_ptr = nullptr);

    void setWeapon(Weapon* weapon_ptr);
    void setTeam(Team* team_ptr);
    Weapon* getWeapon() const;
    void printInfo() const;

private:
    const char* name_;
    ClassName className_;
    Weapon* weapon_ptr_;
    Team* team_ptr_ = nullptr;
    uint16_t healthpoints_ = 100;
};
