#include "vec2d.hpp"

#include <cassert>
#include <cmath>
#include <limits>

size_t Vec2d::instanceCount_ = 0;

Vec2d::Vec2d(float x, float y) : x_(x), y_(y)
{
    ++instanceCount_;
}

Vec2d::Vec2d()
{
}

Vec2d::Vec2d(float x0, float y0, float x1, float y1) : Vec2d(x1 - x0, y1 - y0)
{
}

Vec2d::~Vec2d()
{
    --instanceCount_;
}

bool Vec2d::operator==(const Vec2d& other) const
{
    return (x_ == other.x_) and (y_ == other.y_);
}

Vec2d Vec2d::operator+(const Vec2d& other) const
{
    return Vec2d(x_ + other.x_, y_ + other.y_);
}

Vec2d Vec2d::operator-(const Vec2d& other) const
{
    return Vec2d(x_ - other.x_, y_ - other.y_);
}

float Vec2d::magnitude() const
{
    return std::sqrt(x_ * x_ + y_ * y_);
}

float Vec2d::dotProduct(const Vec2d& other) const
{
    return (x_ * other.x_) + (y_ * other.y_);
}

Vec2d Vec2d::negate() const
{
    return Vec2d(-x_, -y_);
}

Vec2d::RelativeState Vec2d::getRelativeState(const Vec2d& other) const
{
    if (*this == other)
    {
        return Vec2d::RelativeState::Identical;
    }
    const float dotProduct = this->dotProduct(other);
    const float magnitudesProduct = this->magnitude() * other.magnitude();
    if (dotProduct > std::numeric_limits<float>::epsilon())
    {
        if (std::fabs(magnitudesProduct - dotProduct) < std::numeric_limits<float>::epsilon())
        {
            return Vec2d::RelativeState::CoDirected;
        }
        return Vec2d::RelativeState::AcuteAngle;
    }
    if (std::fabs(dotProduct) < std::numeric_limits<float>::epsilon())
    {
        return Vec2d::RelativeState::RightAngle;
    }
    if (std::fabs(magnitudesProduct + dotProduct) < std::numeric_limits<float>::epsilon())
    {
        return Vec2d::RelativeState::OppositeDirected;
    }
    return Vec2d::RelativeState::ObtuseAngle;
}

void Vec2d::scale(float factorX, float factorY)
{
    x_ *= factorX;
    y_ *= factorY;
}

Vec2d& Vec2d::operator=(const Vec2d& other)
{
    if (this == &other)
    {
        return *this;
    }
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}

float& Vec2d::operator[](size_t i)
{
    assert(i < 2);
    if (i == 0) return x_;
    return y_;
}

size_t Vec2d::getInstanceCount()
{
    return instanceCount_;
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
    os << "[" << vec2d.x_ << "; " << vec2d.y_ << "]\n";
    return os;
}

std::istream& operator>>(std::istream& is, Vec2d& vec2d)
{
    is >> vec2d.x_ >> vec2d.y_;
    return is;
}
