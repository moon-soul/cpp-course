#pragma once

#include <iostream>

class Vec3d
{
public:
    Vec3d(float x, float y, float z) : x_(x), y_(y), z_(z) {}

    Vec3d crossProduct(const Vec3d& other) const { return Vec3d(y_ * other.z_ - z_ * other.y_,
                                                                z_ * other.x_ - x_ * other.z_,
                                                                x_ * other.y_ - y_ * other.x_); }

    friend std::ostream& operator<<(std::ostream& os, const Vec3d& vec3d);

private:
    float x_ = 0.f;
    float y_ = 0.f;
    float z_ = 0.f;
};

std::ostream& operator<<(std::ostream& os, const Vec3d& vec3d)
{
    os << "[" << vec3d.x_ << "; " << vec3d.y_ << "; " << vec3d.z_ << "]\n";
    return os;
}
