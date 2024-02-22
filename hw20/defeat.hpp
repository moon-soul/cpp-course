#pragma once

#include <string>

class Munchkin;

class Defeat
{
public:
    virtual ~Defeat() = default;

    virtual std::string getInfo() const = 0;
    virtual void apply(Munchkin* munchkin) = 0;
};

class LevelDowngrade : public Defeat
{
public:
    LevelDowngrade(int level = 1);

    std::string getInfo() const override;
    void apply(Munchkin* munchkin) override;

protected:
    int levelToDowngrade_;
};

class LevelDowngradeIf : public LevelDowngrade
{
public:
    LevelDowngradeIf(int level, int minimalMunchkinLevel);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin) override final;

private:
    int minimalMunchkinLevelToApply_;
};

class WeaponStrongestRemoval : public Defeat
{
public:
    std::string getInfo() const override final;
    void apply(Munchkin* munchkin) override final;
};

class ModifierFromHandRemoval : public Defeat
{
public:
    std::string getInfo() const override final;
    void apply(Munchkin* munchkin) override final;
};
