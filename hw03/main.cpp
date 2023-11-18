#include <iostream>
#include <iomanip>
#include <numbers>

int main()
{
    /* Task 1 */
    int rawSeconds = 0;
    const int secondsInHour = 3600;
    const int secondsInMinute = 60;

    std::cout << "Enter amount of seconds: ";
    std::cin >> rawSeconds;

    const int hours = rawSeconds / secondsInHour;
    rawSeconds %= secondsInHour;
    const int minutes = rawSeconds / secondsInMinute;
    const int seconds = rawSeconds % secondsInMinute;

    std::cout << "\nHours: " << hours
              << "\nMinutes: " << minutes
              << "\nSeconds: " << seconds
              << std::endl;

    /* Task 2 */
    int a = 0;
    int b = 0;
    int c = 0;

    std::cout << "\nEnter first number: ";
    std::cin >> a;
    std::cout << "Enter second number: ";
    std::cin >> b;
    std::cout << "Enter third number: ";
    std::cin >> c;

    std::cout << "\nSum: " << a + b + c
              << "\nProduct: " << a * b * c
              << "\nMean: " << (a + b + c) / 3.0f
              << "\nThe first number is less than or equal to the second number: " << (a <= b)
              << "\nThe second number is less than or equal to the third number: " << (b <= c)
              << std::endl;

    /* Task 3 */
    int x = 0;
    int y = 0;

    std::cout << "\nEnter first number: ";
    std::cin >> x;
    std::cout << "Enter second number: ";
    std::cin >> y;

    const bool lessThan = x < y;
    const bool equal = x == y;
    const bool moreThan = x > y;
    const bool lessOrEqual = x <= y;

    std::cout << std::boolalpha
              << "\nThe first number is less than the second number: " << lessThan
              << "\nThe first number is equal to the second number: " << equal
              << "\nThe first number is more than the second number: " << moreThan
              << "\nThe first number is less than or equal to the second number: " << lessOrEqual
              << std::endl;

    /* Task 4 */
    float rectangleWidth = 0.0f;
    float rectangleHeight = 0.0f;

    std::cout << "\nEnter rectangle width: ";
    std::cin >> rectangleWidth;
    std::cout << "Enter rectangle height: ";
    std::cin >> rectangleHeight;

    const float rectangleArea = rectangleWidth * rectangleHeight;
    const float rectanglePerimeter = (rectangleWidth + rectangleHeight) * 2.0f;

    std::cout << "\nRectangle area: " << rectangleArea
              << "\nRectangle perimeter: " << rectanglePerimeter
              << std::endl;

    /* Task 5 */
    float circleRadius = 0.0f;

    std::cout << "\nEnter circle radius: ";
    std::cin >> circleRadius;

    const float circleArea = std::numbers::pi_v<float> * circleRadius * circleRadius; // C++20
    const float circumference = std::numbers::pi_v<float> * circleRadius * 2.0f; // C++20

    std::cout << "\nCircle area: " << circleArea
              << "\nCircumference: " << circumference
              << std::endl;

    return 0;
}
