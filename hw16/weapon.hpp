#pragma once

#include <string>

class Weapon
{
public:
    Weapon(const char* name, uint16_t damage, uint16_t range);

    std::string getName() const;
    void printInfo() const;

private:
    const char* name_;
    uint16_t damage_;
    uint16_t range_;
};
