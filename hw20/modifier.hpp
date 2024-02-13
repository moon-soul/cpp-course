#pragma once

#include <memory>
#include <string>

#include "monster_tribe.hpp"

class Munchkin;
class Monster;

class Modifier
{
public:
    Modifier() = default;
    virtual ~Modifier() = default;

    virtual std::string getInfo() const = 0;
    virtual int getMunchkinModifier() const;
    virtual int getMonsterModifier() const;

    virtual void apply(Munchkin* munchkin, const std::shared_ptr<Monster>& monster) = 0;

protected:
    int munchkinPowerChange_ = 0;
    int monsterPowerChange_ = 0;
};

class BasicModifier : public Modifier
{
public:
    BasicModifier(int powerBoost);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin, const std::shared_ptr<Monster>& monster) override final;

private:
    int powerBoost_;
};

class DoubleMunchkinLevel : public Modifier
{
public:
    std::string getInfo() const override final;
    void apply(Munchkin* munchkin, const std::shared_ptr<Monster>& monster) override final;
};

class HalveMonsterLevel : public Modifier
{
public:
    HalveMonsterLevel(MonsterTribe tribe);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin, const std::shared_ptr<Monster>& monster) override final;

private:
    MonsterTribe tribe_;
};

class LuckyLevel : public Modifier
{
public:
    LuckyLevel(int level);

    std::string getInfo() const override final;
    void apply(Munchkin* munchkin, const std::shared_ptr<Monster>& monster) override final;

private:
    int level_;
};

class ModifierDelegator
{
public:
    enum class ModifierType
    {
        Basic,
        Double,
        Halve,
        Lucky,
        None
    };

    std::shared_ptr<Modifier> operator()(const std::string& lineToParse) const;

private:
    inline ModifierDelegator::ModifierType mapStrToType(const std::string& typeName) const;
};
