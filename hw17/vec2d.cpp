#include "vec2d.hpp"

#include <cassert>
#include <cmath>

size_t Vec2d::instanceCount = 0;

Vec2d::Vec2d()
{
    ++instanceCount;
}

Vec2d::Vec2d(float x, float y) : x_(x), y_(y)
{
    ++instanceCount;
}

Vec2d::~Vec2d()
{
    --instanceCount;
}

Vec2d& Vec2d::operator=(const Vec2d& vec2d)
{
    if (this == &vec2d)
    {
        return *this;
    }
    x_ = vec2d.x_;
    y_ = vec2d.y_;
    return *this;
}

Vec2d Vec2d::operator+(const Vec2d& vec2d) const
{
    return Vec2d(x_ + vec2d.x_, y_ + vec2d.y_);
}

Vec2d Vec2d::operator-(const Vec2d& vec2d) const
{
    return Vec2d(x_ - vec2d.x_, y_ - vec2d.y_);
}

float Vec2d::operator()() const
{
    return std::sqrt(x_ * x_ + y_ * y_);
}

float& Vec2d::operator[](size_t i)
{
    assert(i == 0 or i == 1);
    if (i == 0) return x_;
    return y_;
}

size_t Vec2d::getInstanceCount()
{
    return instanceCount;
}

Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs)
{
    return Vec2d(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs)
{
    return Vec2d(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
}

std::ostream& operator<<(std::ostream& os, const Vec2d& vec2d)
{
    os << '{' << vec2d.x_ << "; " << vec2d.y_ << '}';
    return os;
}

std::istream& operator>>(std::istream& is, Vec2d& vec2d)
{
    is >> vec2d.x_ >> vec2d.y_;
    return is;
}
