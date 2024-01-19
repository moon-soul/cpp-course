#include "team.hpp"

#include <iostream>

Team::Team(const char* name) : name_(name)
{
}

bool Team::addPlayer(Player* player)
{
    if (player == nullptr)
    {
        return false;
    }
    const auto result = players_.insert(player);
    if (result.second)
    {
        player->setTeam(this);
        ++playersCount_;
    }
    return result.second;
}

bool Team::removePlayer(Player* player)
{
    const auto result = players_.erase(player);
    if (result)
    {
        player->setTeam(nullptr);
        --playersCount_;
    }
    return result;
}

std::string Team::getName() const
{
    return name_;
}

void Team::printInfo() const
{
    for (const Player* player : players_)
    {
        std::cout << "\nTeam [" << name_ << ']';
        player->printInfo();
    }
}
