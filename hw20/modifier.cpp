#include "modifier.hpp"

#include <cassert>
#include <sstream>
#include <vector>

#include "monster.hpp"
#include "munchkin.hpp"
#include "utility.hpp"

int Modifier::getMunchkinModifier() const
{
    return munchkinPowerChange_;
}

int Modifier::getMonsterModifier() const
{
    return monsterPowerChange_;
}

BasicModifier::BasicModifier(int powerBoost) : powerBoost_(powerBoost)
{
}

std::string BasicModifier::getInfo() const
{
    return "<Munchkin power (+" + std::to_string(powerBoost_) + ")>\n";
}

void BasicModifier::apply([[maybe_unused]] Munchkin* munchkin, [[maybe_unused]] const std::shared_ptr<Monster>& monster)
{
    munchkinPowerChange_ = powerBoost_;
}

std::string DoubleMunchkinLevel::getInfo() const
{
    return "<Munchkin level (doubles)>\n";
}

void DoubleMunchkinLevel::apply(Munchkin* munchkin, [[maybe_unused]] const std::shared_ptr<Monster>& monster)
{
    munchkinPowerChange_ = munchkin->getLevel();
}

HalveMonsterLevel::HalveMonsterLevel(MonsterTribe tribe) : tribe_(tribe)
{
}

std::string HalveMonsterLevel::getInfo() const
{
    return "<Monster of tribe {" + Helpers::mapMonsterTribeToStr(tribe_) + "} level (halves)>\n";
}

void HalveMonsterLevel::apply([[maybe_unused]] Munchkin* munchkin, const std::shared_ptr<Monster>& monster)
{
    if (tribe_ == monster->getTribe())
    {
        monsterPowerChange_ = -monster->getLevel() / 2;
    }
}

LuckyLevel::LuckyLevel(int level) : level_(level)
{
}

std::string LuckyLevel::getInfo() const
{
    const std::string levelStr = std::to_string(level_);
    return "<If Monster {level % " + levelStr + " == 0}, Munchkin power (+" + levelStr + ")>\n";
}

void LuckyLevel::apply([[maybe_unused]] Munchkin* munchkin, const std::shared_ptr<Monster>& monster)
{
    if (monster->getLevel() % level_ == 0)
    {
        munchkinPowerChange_ = level_;
    }
}

std::shared_ptr<Modifier> ModifierDelegator::operator()(const std::string& lineToParse) const
{
    assert(not lineToParse.empty());
    constexpr size_t modifierTokens = 2;
    std::vector<std::string> tokens;
    tokens.reserve(modifierTokens);
    std::istringstream iss(lineToParse);
    std::string buffStr;
    while (std::getline(iss, buffStr, ';'))
    {
        tokens.emplace_back(buffStr);
    }
    const std::string typeName = tokens[0];
    const ModifierDelegator::ModifierType type = mapStrToType(typeName);
    switch (type)
    {
    case ModifierDelegator::ModifierType::Basic: return std::make_shared<BasicModifier>(std::stoi(tokens[1]));
    case ModifierDelegator::ModifierType::Double: return std::make_shared<DoubleMunchkinLevel>();
    case ModifierDelegator::ModifierType::Halve: return std::make_shared<HalveMonsterLevel>(Helpers::mapStrToMonsterTribe(tokens[1]));
    case ModifierDelegator::ModifierType::Lucky: return std::make_shared<LuckyLevel>(std::stoi(tokens[1]));
    case ModifierDelegator::ModifierType::None: return nullptr;
    }
}

inline ModifierDelegator::ModifierType ModifierDelegator::mapStrToType(const std::string& typeName) const
{
    if (typeName == Constants::ModifierTypeName::BASIC) return ModifierDelegator::ModifierType::Basic;
    if (typeName == Constants::ModifierTypeName::DOUBLE) return ModifierDelegator::ModifierType::Double;
    if (typeName == Constants::ModifierTypeName::HALVE) return ModifierDelegator::ModifierType::Halve;
    if (typeName == Constants::ModifierTypeName::LUCKY) return ModifierDelegator::ModifierType::Lucky;
    return ModifierDelegator::ModifierType::None;
}
