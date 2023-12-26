#include "rectangle.hpp"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(float length, float height) : length_(length), height_(height)
{
}

float Rectangle::getArea() const
{
    return length_ * height_;
}

float Rectangle::getPerimeter() const
{
    return 2.0f * (length_ + height_);
}
