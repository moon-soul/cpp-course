#include "weapon.hpp"

int RangedWeapon::getDamageRate(size_t distance) const
{
    return static_cast<int>(getPrecision(distance) * 10);
}

std::string SniperRifle::getName() const
{
    return "SniperRifle";
}

float SniperRifle::getPrecision(size_t distance) const
{
    if (distance > 2000)
    {
        return 0.2f;
    }
    if (distance > 1000)
    {
        return 1.5f;
    }
    if (distance > 300)
    {
        return 5.0f;
    }
    return 1.0f;
}

std::string AssaultRifle::getName() const
{
    return "AssaultRifle";
}

float AssaultRifle::getPrecision(size_t distance) const
{
    if (distance > 2000)
    {
        return 0.1f;
    }
    if (distance > 1000)
    {
        return 1.0f;
    }
    if (distance > 300)
    {
        return 3.0f;
    }
    return 3.0f;
}

std::string Pistol::getName() const
{
    return "Pistol";
}

float Pistol::getPrecision(size_t distance) const
{
    if (distance > 2000)
    {
        return 0.05f;
    }
    if (distance > 1000)
    {
        return 0.5f;
    }
    if (distance > 300)
    {
        return 1.0f;
    }
    return 5.0f;
}

int MeleeWeapon::getDamageRate(size_t distance) const
{
    return static_cast<int>(getEffectiveRangeMultiplier(distance) * 10);
}

std::string BareHand::getName() const
{
    return "BareHand";
}

float BareHand::getEffectiveRangeMultiplier(size_t distance) const
{
    return distance > 50 ? 0.0f : 1.0f;
}

std::string Sword::getName() const
{
    return "Sword";
}

float Sword::getEffectiveRangeMultiplier(size_t distance) const
{
    return distance > 150 ? 0.0f : 7.5f;
}
