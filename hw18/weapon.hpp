#pragma once

#include <string>

class Weapon
{
public:
    virtual ~Weapon() = default;

    virtual int getDamageRate(size_t distance) const = 0;
    virtual std::string getName() const = 0;
};

class RangedWeapon : public Weapon
{
public:
    virtual int getDamageRate(size_t distance) const override;
    virtual std::string getName() const override = 0;

protected:
    virtual float getPrecision(size_t distance) const = 0;
};

class SniperRifle : public RangedWeapon
{
public:
    virtual std::string getName() const override;

protected:
    virtual float getPrecision(size_t distance) const override;
};

class AssaultRifle : public RangedWeapon
{
public:
    virtual std::string getName() const override;

protected:
    virtual float getPrecision(size_t distance) const override;
};

class Pistol : public RangedWeapon
{
public:
    virtual std::string getName() const override;

protected:
    virtual float getPrecision(size_t distance) const override;
};

class MeleeWeapon : public Weapon
{
public:
    virtual int getDamageRate(size_t distance) const override;
    virtual std::string getName() const override = 0;

protected:
    virtual float getEffectiveRangeMultiplier(size_t distance) const = 0;
};

class BareHand : public MeleeWeapon
{
public:
    virtual std::string getName() const override;

protected:
    virtual float getEffectiveRangeMultiplier(size_t distance) const override;
};

class Sword : public MeleeWeapon
{
public:
    virtual std::string getName() const override;

protected:
    virtual float getEffectiveRangeMultiplier(size_t distance) const override;
};
