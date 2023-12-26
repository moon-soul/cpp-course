#include "class_name.hpp"

std::string Helper::classNameToStr(ClassName className)
{
    switch (className)
    {
    case ClassName::Assault: return "Assault";
    case ClassName::Support: return "Support";
    case ClassName::Sniper: return "Sniper";
    case ClassName::Medic: return "Medic";
    default: return "Undefined";
    }
}
