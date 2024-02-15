#include <iostream>

#include "vec2d.hpp"
#include "vec3d.hpp"

int main()
{
    /* Homework 17 */
    /* Task 1 */
    Vec2d vec;
    const Vec2d vec1(10.2f, 10.2f);
    std::cout << "vec: " << vec
              << "vec1: " << vec1;

    /* Task 2 */
    vec = vec1;
    std::cout << "\nvec: " << vec;

    /* Task 3 */
    vec = vec1.operator+(vec1);
    std::cout << "\nvec: " << vec;
    vec = vec1.operator-(Vec2d(4.2f, 4.2f));
    std::cout << "vec: " << vec;

    // vec = vec1 + vec1; // More than one operator "+" matches these operands

    /* Task 4 */
    vec = operator+(vec1, vec1);
    std::cout << "\nvec: " << vec;
    vec = operator-(vec1, Vec2d(4.2f, 4.2f));
    std::cout << "vec: " << vec;

    /* Task 5 */
    std::cout << "\nvec magnitude: " << vec.magnitude() << '\n';

    /* Task 6 */
    vec[0] = 2.2f;
    vec[1] = 8.8f;

    /* Task 7 */
    std::cout << "\nvec: " << vec;

    /* Task 8 */
    std::cout << "\nEnter vec: ";
    std::cin >> vec;
    std::cout << "vec: " << vec;

    /* Task 9 */
    {
        const Vec2d vec2;
        std::cout << "\nVec2d instance count: " << Vec2d::getInstanceCount() << '\n';
    }
    std::cout << "Vec2d instance count: " << Vec2d::getInstanceCount() << '\n';
    /* End of homework 17 */

    /* Homework 26 */
    /* Task 1 */
    const Vec2d vec2d_1(0.f, 0.f, 2.2f, 4.4f);
    std::cout << "\nvec2d_1: " << vec2d_1;

    /* Task 2 */
    std::cout << "\nEnter vec2d_2: ";
    Vec2d vec2d_2;
    std::cin >> vec2d_2;
    std::cout << "vec2d_2: " << vec2d_2;

    std::cout << "\nvec2d_1 . vec2d_2: " << vec2d_1.dotProduct(vec2d_2) << '\n';

    /* Task 3 */
    std::cout << "\nvec2d_1 negated: " << vec2d_1.negate();

    /* Task 4 */
    std::cout << "\nvec2d_1 relation to vec2d_2: ";
    const Vec2d::RelativeState state = vec2d_1.getRelativeState(vec2d_2);
    switch (state)
    {
    case Vec2d::RelativeState::Identical:
        std::cout << "Identical";
        break;
    case Vec2d::RelativeState::CoDirected:
        std::cout << "Same Directions";
        break;
    case Vec2d::RelativeState::AcuteAngle:
        std::cout << "Angle is Acute";
        break;
    case Vec2d::RelativeState::RightAngle:
        std::cout << "Angle is Right";
        break;
    case Vec2d::RelativeState::OppositeDirected:
        std::cout << "Opposite Directions";
        break;
    case Vec2d::RelativeState::ObtuseAngle:
        std::cout << "Angle is Obtuse";
        break;
    default:
        std::cout << "Unknown";
        break;
    }
    std::cout << '\n';

    /* Task 5 */
    constexpr float factorX = 2.f;
    constexpr float factorY = 0.5f;
    vec2d_2.scale(factorX, factorY);
    std::cout << "\nvec2d_2 scaled by factorX = " << factorX << ", factorY = " << factorY << ": " << vec2d_2;

    /* Task 6 */
    const Vec3d vec3d_1(2.f, 3.f, 4.f);
    const Vec3d vec3d_2(1.f, 2.f, 3.f);
    std::cout << "\nvec3d_1: " << vec3d_1
              << "vec3d_2: " << vec3d_2
              << "\nvec3d_1 x vec3d_2: " << vec3d_1.crossProduct(vec3d_2);
    /* End of homework 26 */

    return 0;
}
