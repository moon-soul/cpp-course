#pragma once

#include <string>

#include "monster_tribe.hpp"

namespace Constants
{

namespace WeaponTypeName
{

const std::string COMMON = "COMMON";
const std::string UNDEAD = "UNDEAD";
const std::string HOLY = "HOLY";
const std::string LEGENDARY = "LEGENDARY";
const std::string UNKNOWN = "UNKNOWN";

} // namespace WeaponTypeName

namespace ModifierTypeName
{

const std::string BASIC = "BASIC";
const std::string DOUBLE = "DOUBLE";
const std::string HALVE = "HALVE";
const std::string LUCKY = "LUCKY";

} // namespace ModifierTypeName

namespace MonsterTribeName
{

const std::string HUMAN = "HUMAN";
const std::string UNDEAD = "UNDEAD";
const std::string ZOMBIE = "ZOMBIE";
const std::string GOD = "GOD";

} // namespace MonsterTribeName

namespace FilePath
{

const std::string WEAPONS_FILE_PATH = "weapons.txt";
const std::string MODIFIERS_FILE_PATH = "modifiers.txt";
const std::string MONSTERS_FILE_PATH = "monsters.txt";

} // namespace FilePath

const std::string DEFAULT_MUNCHKIN_NAME = "__blank__";
constexpr int WINNING_LEVEL = 10;
constexpr size_t INITIAL_WEAPONS = 1;
constexpr size_t INITIAL_MODIFIERS = 5;

} // namespace Constants

namespace Helpers
{

inline std::string mapMonsterTribeToStr(MonsterTribe tribe)
{
    switch (tribe)
    {
    case MonsterTribe::Human: return Constants::MonsterTribeName::HUMAN;
    case MonsterTribe::Undead: return Constants::MonsterTribeName::UNDEAD;
    case MonsterTribe::Zombie: return Constants::MonsterTribeName::ZOMBIE;
    case MonsterTribe::God: return Constants::MonsterTribeName::GOD;
    default: return "";
    }
}

inline MonsterTribe mapStrToMonsterTribe(const std::string& tribeName)
{
    if (tribeName == Constants::MonsterTribeName::HUMAN) return MonsterTribe::Human;
    if (tribeName == Constants::MonsterTribeName::UNDEAD) return MonsterTribe::Undead;
    if (tribeName == Constants::MonsterTribeName::ZOMBIE) return MonsterTribe::Zombie;
    if (tribeName == Constants::MonsterTribeName::GOD) return MonsterTribe::God;
    return MonsterTribe::Last;
}

} // namespace Helpers
