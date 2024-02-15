#pragma once

#include <cstddef>
#include <iostream>

class Vec2d
{
public:
    enum class RelativeState
    {
        Identical,
        CoDirected,
        AcuteAngle,
        RightAngle,
        OppositeDirected,
        ObtuseAngle,
    };

    Vec2d();
    Vec2d(float x1, float y1);
    Vec2d(float x0, float y0, float x1, float y1);
    ~Vec2d();

    bool operator==(const Vec2d& other) const;
    Vec2d operator+(const Vec2d& other) const;
    Vec2d operator-(const Vec2d& other) const;
    float magnitude() const;
    float dotProduct(const Vec2d& other) const;
    Vec2d negate() const;
    Vec2d::RelativeState getRelativeState(const Vec2d& other) const;
    void scale(float factorX, float factorY);
    Vec2d& operator=(const Vec2d& other);
    float& operator[](size_t i);

    static size_t getInstanceCount();

    friend Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs);
    friend Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Vec2d& vec2d);
    friend std::istream& operator>>(std::istream& is, Vec2d& vec2d);

private:
    float x0_ = 0.f;
    float y0_ = 0.f;
    float x1_ = 0.f;
    float y1_ = 0.f;
    static size_t instanceCount_;
};

Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs);
Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs);
std::ostream& operator<<(std::ostream& os, const Vec2d& vec2d);
std::istream& operator>>(std::istream& is, Vec2d& vec2d);
