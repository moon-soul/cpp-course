#pragma once

class PlayerClass
{
public:
    virtual ~PlayerClass() = default;

    virtual float getDamageMultiplier() const = 0;
    virtual float getArmorMultiplier() const = 0;
    virtual float getMissChance() const = 0;
};

class DefaultClass : public PlayerClass
{
public:
    virtual float getDamageMultiplier() const override { return 1.0f; }
    virtual float getArmorMultiplier() const override { return 1.0f; }
    virtual float getMissChance() const override { return 0.0f; }
};

class AttackerClass : public virtual DefaultClass
{
public:
    virtual float getDamageMultiplier() const override { return 1.3f; }
    virtual float getArmorMultiplier() const override { return 0.8f; }
};

class DefenderClass : public DefaultClass
{
public:
    virtual float getDamageMultiplier() const override { return 0.8f; }
    virtual float getArmorMultiplier() const override { return 1.2f; }
    virtual float getMissChance() const override { return 0.1f; }
};

class LuckymanClass : public virtual DefaultClass
{
public:
    virtual float getMissChance() const override { return 0.3f; }
};

class BerserkClass : public AttackerClass, LuckymanClass
{
public:
    virtual float getArmorMultiplier() const override { return 0.3f; }
};
