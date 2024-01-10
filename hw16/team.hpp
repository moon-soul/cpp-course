#pragma once

#include <string>
#include <unordered_set>

#include "player.hpp"

class Player;

class Team
{
public:
    Team(const char* name);

    bool addPlayer(Player* player);
    bool removePlayer(Player* player);
    std::string getName() const;
    void printInfo() const;

private:
    const char* name_;
    std::unordered_set<Player*> players_;
    size_t playersCount_ = 0;
};
