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

    const std::shared_ptr<Type> getUniqueEntry();

private:
    std::vector<std::shared_ptr<Type>> database_;
    std::vector<std::shared_ptr<Type>> available_;
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
    available_ = database_;
    std::random_shuffle(available_.begin(), available_.end());
}

template<class Type>
const std::shared_ptr<Type> Deck<Type>::getUniqueEntry()
{
    if (available_.size() == 0)
    {
        available_ = database_;
        std::random_shuffle(available_.begin(), available_.end());
    }
    const auto uniqueEntry = available_.front();
    available_.erase(available_.begin());
    return uniqueEntry;
}
