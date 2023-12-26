#include "player.hpp"

#include <iostream>
#include <string>

Player::Player(const char* name, ClassName className, Weapon* weapon_ptr)
    : name_(name), className_(className), weapon_ptr_(weapon_ptr)
{
}

void Player::setWeapon(Weapon* weapon_ptr)
{
    weapon_ptr_ = weapon_ptr;
}

void Player::setTeam(Team* team_ptr)
{
    team_ptr_ = team_ptr;
}

Weapon* Player::getWeapon() const
{
    return weapon_ptr_;
}

void Player::printInfo() const
{
    const std::string weapon = weapon_ptr_ ? weapon_ptr_->getName() : "unequipped";
    const std::string team = team_ptr_ ? team_ptr_->getName() : "none";
    std::cout << "\nPlayer [" << name_ << ']'
              << "\nHealth: " << healthpoints_
              << "\nClass: " << Helper::classNameToStr(className_)
              << "\nWeapon: " << weapon
              << "\nTeam: " << team
              << '\n';
}
