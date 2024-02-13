#pragma once

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

template<class Type>
class Deck
{
public:
    Deck(const std::string& filename, std::function<std::shared_ptr<Type>(const std::string&)> constructObj, size_t reserveSpace = 10);

    const std::shared_ptr<Type>& getUniqueEntry();

private:
    std::vector<std::shared_ptr<Type>> database_;
    std::unordered_set<size_t> used_;
};

template<class Type>
Deck<Type>::Deck(const std::string& filename, std::function<std::shared_ptr<Type>(const std::string&)> constructObj, size_t reserveSpace)
{
    assert(not filename.empty());
    std::ifstream storageFile(filename);
    assert(storageFile.is_open());
    database_.reserve(reserveSpace);
    std::string buffStr;
    while (std::getline(storageFile, buffStr))
    {
        std::transform(buffStr.begin(), buffStr.end(), buffStr.begin(), ::toupper);
        database_.emplace_back(constructObj(buffStr));
    }
    storageFile.close();
    std::random_shuffle(database_.begin(), database_.end());
}

template<class Type>
const std::shared_ptr<Type>& Deck<Type>::getUniqueEntry()
{
    if (used_.size() == database_.size())
    {
        used_.clear();
        std::random_shuffle(database_.begin(), database_.end());
    }
    size_t randomPos = std::rand() % database_.size();
    while (used_.contains(randomPos))
    {
        randomPos = std::rand() % database_.size();
    }
    used_.insert(randomPos);
    return database_[randomPos];
}
