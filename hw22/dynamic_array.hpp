#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>

template<class Type>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(const DynamicArray<Type>& other);
    ~DynamicArray();

    DynamicArray<Type>& operator=(const DynamicArray<Type>& other);
    Type& operator[](size_t index);
    bool operator==(const DynamicArray<Type>& other) const;

    bool isEmpty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    Type back() const;
    void reserve(size_t reservedSpace);
    void shrinkToFit();
    void setSize(size_t newSize);
    void clear();
    void push_back(Type element);
    void pop_back();

private:
    inline void reallocate(size_t newCapacity, size_t endPos, bool fillWithNulls = false);

    size_t size_ = 0;
    size_t capacity_ = 1;
    Type* arr_ = new Type[capacity_];
};

template<class Type>
DynamicArray<Type>::DynamicArray()
{
}

template<class Type>
DynamicArray<Type>::DynamicArray(size_t size)
    : size_(size),
      capacity_(size_ > 0 ? size_ : 1),
      arr_(new Type[capacity_]())
{
}

template<class Type>
DynamicArray<Type>::DynamicArray(const DynamicArray<Type>& other)
    : size_(other.size_),
      capacity_(size_ > 0 ? size_ : 1),
      arr_(new Type[capacity_])
{
    if (other.size_ > 0)
    {
        std::copy(other.arr_, other.arr_ + other.size_, arr_);
    }
}

template<class Type>
DynamicArray<Type>::~DynamicArray()
{
    if (arr_ != nullptr)
    {
        delete[] arr_;
    }
}

template<class Type>
DynamicArray<Type>& DynamicArray<Type>::operator=(const DynamicArray<Type>& other)
{
    if (capacity_ < other.size_)
    {
        if (arr_ != nullptr)
        {
            delete[] arr_;
        }
        capacity_ = other.size_;
        arr_ = new Type[capacity_];
    }
    size_ = other.size_;
    if (other.size_ > 0)
    {
        std::copy(other.arr_, other.arr_ + other.size_, arr_);
    }
    return *this;
}

template<class Type>
Type& DynamicArray<Type>::operator[](size_t index)
{
    assert(index < size_);
    return arr_[index];
}

template<class Type>
bool DynamicArray<Type>::operator==(const DynamicArray<Type>& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    for (size_t i = 0; i < size_; ++i)
    {
        if (arr_[i] != other.arr_[i])
        {
            return false;
        }
    }
    return true;
}

template<class Type>
bool DynamicArray<Type>::isEmpty() const
{
    return size_ == 0;
}

template<class Type>
size_t DynamicArray<Type>::getSize() const
{
    return size_;
}

template<class Type>
size_t DynamicArray<Type>::getCapacity() const
{
    return capacity_;
}

template<class Type>
Type DynamicArray<Type>::back() const
{
    assert(size_ > 0);
    return arr_[size_ - 1];
}

template<class Type>
void DynamicArray<Type>::reserve(size_t reservedSpace)
{
    if (capacity_ >= reservedSpace)
    {
        return;
    }
    reallocate(reservedSpace, size_);
}

template<class Type>
void DynamicArray<Type>::shrinkToFit()
{
    if (capacity_ == size_)
    {
        return;
    }
    if (size_ == 0)
    {
        reallocate(1, 0);
        return;
    }
    reallocate(size_, size_);
}

template<class Type>
void DynamicArray<Type>::setSize(size_t newSize)
{
    if (size_ == newSize)
    {
        return;
    }
    if (capacity_ < newSize)
    {
        reallocate(newSize, size_, true);
    }
    else if (size_ < newSize)
    {
        for (size_t i = size_; i < newSize; ++i)
        {
            arr_[i] = 0;
        }
    }
    size_ = newSize;
}

template<class Type>
void DynamicArray<Type>::clear()
{
    size_ = 0;
}

template<class Type>
void DynamicArray<Type>::push_back(Type element)
{
    const size_t prevSize = size_;
    ++size_;
    if (capacity_ < size_)
    {
        reallocate(capacity_ * 2, prevSize);
    }
    arr_[prevSize] = element;
}

template<class Type>
void DynamicArray<Type>::pop_back()
{
    if (size_ > 0)
    {
        --size_;
    }
}

template<class Type>
inline void DynamicArray<Type>::reallocate(size_t newCapacity, size_t endPos, bool fillWithNulls)
{
    capacity_ = newCapacity;
    Type* newArr = fillWithNulls ? new Type[capacity_]() : new Type[capacity_];
    if (endPos > 0)
    {
        std::copy(arr_, arr_ + endPos, newArr);
    }
    if (arr_ != nullptr)
    {
        delete[] arr_;
    }
    arr_ = newArr;
}
