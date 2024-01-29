#include "player.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

Player::Player(const std::string& name,
               Weapon* weapon,
               PlayerClass* playerClass)
    : name_(name), weapon_(weapon), playerClass_(playerClass)
{
}

Player::~Player()
{
    if (weapon_ != nullptr)
    {
        delete weapon_;
    }
    if (playerClass_ != nullptr)
    {
        delete playerClass_;
    }
}

std::string Player::getName() const
{
    return name_;
}

std::string Player::getCurrentWeaponName() const
{
    return weapon_ ? weapon_->getName() : "Unequipped";
}

int Player::getHealthpoints() const
{
    return healthpoints_;
}

int Player::getBaseDamage(size_t distance) const
{
    if (weapon_ == nullptr)
    {
        return 0;
    }
    return weapon_->getDamageRate(distance);
}

float Player::getClassAttackBonus() const
{
    if (playerClass_ == nullptr)
    {
        return 1.0f;
    }
    return playerClass_->getDamageMultiplier();
}

float Player::getClassDefenseBonus() const
{
    if (playerClass_ == nullptr)
    {
        return 1.0f;
    }
    return playerClass_->getArmorMultiplier();
}

float Player::getClassMissChance() const
{
    if (playerClass_ == nullptr)
    {
        return 0.0f;
    }
    return playerClass_->getMissChance();
}

bool Player::isEliminated() const
{
    return healthpoints_ <= 0;
}

void Player::setWeapon(Weapon* weapon)
{
    if (weapon == nullptr)
    {
        return;
    }
    if (weapon_ != nullptr)
    {
        delete weapon_;
    }
    weapon_ = weapon;
}

void Player::setPlayerClass(PlayerClass* playerClass)
{
    if (playerClass == nullptr)
    {
        return;
    }
    if (playerClass_ != nullptr)
    {
        delete playerClass_;
    }
    playerClass_ = playerClass;
}

void Player::attack(Player& attacked, size_t distance)
{
    if (this == &attacked)
    {
        std::cout << "\nDon't hurt yourself!\n";
        return;
    }
    const std::string attackingPlayerName = getName();
    if (isEliminated())
    {
        std::cout << "\nPlayer [" << attackingPlayerName << "] has already been eliminated and cannot attack!\n";
        return;
    }
    const std::string attackedPlayerName = attacked.getName();
    if (attacked.isEliminated())
    {
        std::cout << "\nPlayer [" << attackedPlayerName << "] has already been eliminated!\n";
        return;
    }
    if (distance == 0)
    {
        std::cout << "\nGetting inside your opponent is strictly prohibited!\n";
        return;
    }

    std::srand(std::time(nullptr));
    const int randomNumber = std::rand() % 100 + 1;
    const bool isHit = (randomNumber > (attacked.getClassMissChance() * 100));
    int outcomingDamage = 0;
    if (isHit)
    {
        outcomingDamage = static_cast<int>(getBaseDamage(distance) * getClassAttackBonus() / attacked.getClassDefenseBonus());
        attacked.setHealthpoints(attacked.getHealthpoints() - outcomingDamage);
    }

    std::cout << "\nPlayer [" << attackingPlayerName << "] has attacked player [" << attackedPlayerName
              << "] with weapon {" << getCurrentWeaponName() << "} with damage (" << outcomingDamage << ")\n"
              << "Player [" << attackedPlayerName << "] has (" << attacked.getHealthpoints() << ") HP left\n";

    if (attacked.isEliminated())
    {
        std::cout << "Player [" << attackedPlayerName << "] has just been eliminated!\n";
    }
}

void Player::setHealthpoints(int healthpoints)
{
    healthpoints_ = healthpoints;
    if (healthpoints_ < 0)
    {
        healthpoints_ = 0;
    }
}
