#include <iostream>

#include "vec2d.hpp"

int main()
{
    /* Task 1 */
    Vec2d vec;
    const Vec2d vec1(10.2f, 10.2f);
    std::cout << "vec: " << vec
              << "\nvec1: " << vec1
              << '\n';

    /* Task 2 */
    vec = vec1;
    std::cout << "\nvec: " << vec << '\n';

    /* Task 3 */
    vec = vec1.operator+(vec1);
    std::cout << "\nvec: " << vec << '\n';
    vec = vec1.operator-(Vec2d(4.2f, 4.2f));
    std::cout << "vec: " << vec << '\n';

    /* Task 4 */
    vec = operator+(vec1, vec1);
    std::cout << "\nvec: " << vec << '\n';
    vec = operator-(vec1, Vec2d(4.2f, 4.2f));
    std::cout << "vec: " << vec << '\n';

    /* Task 5 */
    std::cout << "\nvec magnitude: " << vec() << '\n';

    /* Task 6 */
    vec[0] = 2.2f;
    vec[1] = 8.8f;

    /* Task 7 */
    std::cout << "\nvec: " << vec << '\n';

    /* Task 8 */
    std::cout << "\nEnter vec: ";
    std::cin >> vec;
    std::cout << "vec: " << vec << '\n';

    /* Task 9 */
    {
        const Vec2d vec2;
        std::cout << "\nVec2d instance count: " << Vec2d::getInstanceCount() << '\n';
    }
    std::cout << "Vec2d instance count: " << Vec2d::getInstanceCount() << '\n';

    return 0;
}
