#pragma once

#include <string>

enum class ClassName
{
    Assault,
    Support,
    Sniper,
    Medic,
    Last
};

namespace Helper
{

std::string classNameToStr(ClassName className);

} // namespace Helper
