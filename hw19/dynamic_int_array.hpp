#pragma once

#include <cstdlib>

class DynamicIntArray
{
public:
    DynamicIntArray();
    DynamicIntArray(size_t size);
    DynamicIntArray(const DynamicIntArray& other);
    ~DynamicIntArray();

    DynamicIntArray& operator=(const DynamicIntArray& other);
    int& operator[](size_t index);

    bool isEmpty() const;
    size_t getSize() const;
    void setSize(size_t newSize);
    void clear();
    void push_back(int element);

private:
    size_t size_ = 0;
    int* arr_ = nullptr;
};
