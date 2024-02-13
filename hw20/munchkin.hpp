#pragma once

#include <memory>
#include <string>
#include <vector>

class Weapon;
class Modifier;

class Munchkin
{
public:
    Munchkin(const std::string& name);

    const std::string& getName() const;
    int getLevel() const;
    const std::vector<std::shared_ptr<Weapon>>& getWeapons() const;
    const std::vector<std::shared_ptr<Modifier>>& getModifiers() const;

    void setName(const std::string& name);
    void updateLevelBy(int levels);
    void addWeapon(const std::shared_ptr<Weapon>& weapon);
    void addModifier(const std::shared_ptr<Modifier>& modifier);
    std::shared_ptr<Modifier> popModifier(int pos);
    void removeWeaponEquipped(size_t pos);
    void removeModifierFromHand(size_t pos);

private:
    std::string name_;
    int level_ = 1;
    std::vector<std::shared_ptr<Weapon>> weapons_;
    std::vector<std::shared_ptr<Modifier>> modifiers_;
};
