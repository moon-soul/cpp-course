#include "vec2d.hpp"

#include <cassert>
#include <cmath>
#include <limits>

size_t Vec2d::instanceCount_ = 0;

Vec2d::Vec2d()
{
    ++instanceCount_;
}

Vec2d::Vec2d(float x1, float y1) : x1_(x1), y1_(y1)
{
    ++instanceCount_;
}

Vec2d::Vec2d(float x0, float y0, float x1, float y1) : x0_(x0), y0_(y0), x1_(x1), y1_(y1)
{
    ++instanceCount_;
}

Vec2d::~Vec2d()
{
    --instanceCount_;
}

bool Vec2d::operator==(const Vec2d& other) const
{
    return x0_ == other.x0_ and y0_ == other.y0_ and x1_ == other.x1_ and y1_ == other.y1_;
}

Vec2d Vec2d::operator+(const Vec2d& other) const
{
    return Vec2d(x0_ + other.x0_, y0_ + other.y0_, x1_ + other.x1_, y1_ + other.y1_);
}

Vec2d Vec2d::operator-(const Vec2d& other) const
{
    return Vec2d(x0_ - other.x0_, y0_ - other.y0_, x1_ - other.x1_, y1_ - other.y1_);
}

float Vec2d::magnitude() const
{
    return std::sqrt((x1_ - x0_) * (x1_ - x0_) + (y1_ - y0_) * (y1_ - y0_));
}

float Vec2d::dotProduct(const Vec2d& other) const
{
    return (x1_ - x0_) * (other.x1_ - other.x0_) + (y1_ - y0_) * (other.y1_ - other.y0_);
}

Vec2d Vec2d::negate() const
{
    return Vec2d(x0_ - x1_, y0_ - y1_);
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
        if (std::abs(magnitudesProduct - dotProduct) <= std::numeric_limits<float>::epsilon())
        {
            return Vec2d::RelativeState::CoDirected;
        }
        return Vec2d::RelativeState::AcuteAngle;
    }
    else if (std::abs(dotProduct) <= std::numeric_limits<float>::epsilon())
    {
        return Vec2d::RelativeState::RightAngle;
    }
    else if (std::abs(magnitudesProduct + dotProduct) <= std::numeric_limits<float>::epsilon())
    {
        return Vec2d::RelativeState::OppositeDirected;
    }
    return Vec2d::RelativeState::ObtuseAngle;
}

void Vec2d::scale(float factorX, float factorY)
{
    x0_ *= factorX;
    y0_ *= factorY;
    x1_ *= factorX;
    y1_ *= factorY;
}

Vec2d& Vec2d::operator=(const Vec2d& other)
{
    if (this == &other)
    {
        return *this;
    }
    x0_ = other.x0_;
    y0_ = other.y0_;
    x1_ = other.x1_;
    y1_ = other.y1_;
    return *this;
}

float& Vec2d::operator[](size_t i)
{
    assert(i < 4);
    switch (i)
    {
    case 0: return x0_;
    case 1: return y0_;
    case 2: return x1_;
    default: return y1_;
    }
}

size_t Vec2d::getInstanceCount()
{
    return instanceCount_;
}

Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs)
{
    return Vec2d(lhs.x0_ + rhs.x0_, lhs.y0_ + rhs.y0_, lhs.x1_ + rhs.x1_, lhs.y1_ + rhs.y1_);
}

Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs)
{
    return Vec2d(lhs.x0_ - rhs.x0_, lhs.y0_ - rhs.y0_, lhs.x1_ - rhs.x1_, lhs.y1_ - rhs.y1_);
}

std::ostream& operator<<(std::ostream& os, const Vec2d& vec2d)
{
    os << "[{" << vec2d.x0_ << "; " << vec2d.y0_ << "}, {" << vec2d.x1_ << "; " << vec2d.y1_ << "}]\n";
    return os;
}

std::istream& operator>>(std::istream& is, Vec2d& vec2d)
{
    is >> vec2d.x0_ >> vec2d.y0_ >> vec2d.x1_ >> vec2d.y1_;
    return is;
}
