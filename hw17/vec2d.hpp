#pragma once

#include <iostream>

class Vec2d
{
public:
    Vec2d();
    Vec2d(float x, float y);
    ~Vec2d();

    Vec2d& operator=(const Vec2d& vec2d);
    Vec2d operator+(const Vec2d& vec2d) const;
    Vec2d operator-(const Vec2d& vec2d) const;
    float operator()() const;
    float& operator[](size_t i);

    static size_t getInstanceCount();

    friend Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs);
    friend Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Vec2d& vec2d);
    friend std::istream& operator>>(std::istream& is, Vec2d& vec2d);

private:
    float x_ = 0.0f;
    float y_ = 0.0f;
    static size_t instanceCount;
};

Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs);
Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs);
std::ostream& operator<<(std::ostream& os, const Vec2d& vec2d);
std::istream& operator>>(std::istream& is, Vec2d& vec2d);
