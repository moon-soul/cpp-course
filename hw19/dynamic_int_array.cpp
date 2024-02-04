#include "dynamic_int_array.hpp"

#include <algorithm>
#include <cassert>

DynamicIntArray::DynamicIntArray()
{
}

DynamicIntArray::DynamicIntArray(size_t size)
    : size_(size),
      arr_(size_ > 0 ? new int[size_]() : nullptr)
{
}

DynamicIntArray::DynamicIntArray(const DynamicIntArray& other)
    : size_(other.size_),
      arr_(size_ > 0 ? new int[size_] : nullptr)
{
    if (not other.isEmpty())
    {
        std::copy(other.arr_, other.arr_ + other.size_, arr_);
    }
}

DynamicIntArray::~DynamicIntArray()
{
    if (arr_ != nullptr)
    {
        delete[] arr_;
    }
}

DynamicIntArray& DynamicIntArray::operator=(const DynamicIntArray& other)
{
    if (size_ != other.size_)
    {
        if (arr_ != nullptr)
        {
            delete[] arr_;
        }
        size_ = other.size_;
        arr_ = size_ > 0 ? new int[size_] : nullptr;
    }
    if (not other.isEmpty())
    {
        std::copy(other.arr_, other.arr_ + other.size_, arr_);
    }
    return *this;
}

int& DynamicIntArray::operator[](size_t index)
{
    assert(index < size_);
    return arr_[index];
}

bool DynamicIntArray::isEmpty() const
{
    return (size_ == 0 and arr_ == nullptr);
}

size_t DynamicIntArray::getSize() const
{
    return size_;
}

void DynamicIntArray::setSize(size_t newSize)
{
    if (size_ == newSize)
    {
        return;
    }
    int* newArr = newSize > 0 ? new int[newSize]() : nullptr;
    if (arr_ != nullptr)
    {
        if (newArr != nullptr)
        {
            const size_t limiter = size_ < newSize ? size_ : newSize;
            std::copy(arr_, arr_ + limiter, newArr);
        }
        delete[] arr_;
    }
    size_ = newSize;
    arr_ = newArr;
}

void DynamicIntArray::clear()
{
    if (arr_ != nullptr)
    {
        delete[] arr_;
    }
    size_ = 0;
    arr_ = nullptr;
}

void DynamicIntArray::push_back(int element)
{
    int* newArr = new int[size_ + 1];
    for (size_t i = 0; i < size_; ++i)
    {
        newArr[i] = arr_[i];
    }
    if (arr_ != nullptr)
    {
        delete[] arr_;
    }
    arr_ = newArr;
    arr_[size_] = element;
    ++size_;
}
