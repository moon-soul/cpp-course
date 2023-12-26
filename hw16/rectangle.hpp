#pragma once

class Rectangle
{
public:
    Rectangle();
    Rectangle(float length, float height);

    float getArea() const;
    float getPerimeter() const;

private:
    float length_ = 0.0f;
    float height_ = 0.0f;
};
