#include <iostream>
#include <iomanip>

int main()
{
    /* Task 1 */
    int i = 0;
    int j = 0;

    std::cout << "Enter integer 1: ";
    std::cin >> i;
    std::cout << "Enter integer 2: ";
    std::cin >> j;

    int tmp = i;
    i = j;
    j = tmp;

    std::cout << "\nInteger 1: " << i << "\nInteger 2: " << j << std::endl;

    /* Task 2 */
    double d = 0.0;

    std::cout << "\nEnter floating point number: ";
    std::cin >> d;
    std::cout << "\nFloating point number: " << d << std::endl;

    std::cout << "\nCast floating point to integer:\n"
              << std::right
              << std::setw(20)
              << std::setfill('$')
              << static_cast<int>(d)
              << std::endl;

    /* Task 3 */
    double x = 31415.9265359;

    std::cout << "\nX:\n"
              << std::setprecision(2) << x << std::endl
              << std::setprecision(5) << x << std::endl
              << std::setprecision(10) << x << std::endl
              << std::fixed << x << std::endl
              << std::scientific << x << std::endl;

    /* Task 4 */
    enum class WeekDay
    {
        Monday = 1,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    std::cout << "\nWeekDay"
              << "\nMonday: " << static_cast<int>(WeekDay::Monday)
              << "\nTuesday: " << static_cast<int>(WeekDay::Tuesday)
              << "\nWednesday: " << static_cast<int>(WeekDay::Wednesday)
              << "\nThursday: " << static_cast<int>(WeekDay::Thursday)
              << "\nFriday: " << static_cast<int>(WeekDay::Friday)
              << "\nSaturday: " << static_cast<int>(WeekDay::Saturday)
              << "\nSunday: " << static_cast<int>(WeekDay::Sunday)
              << std::endl;

    /* Task 5 */
    int f = 0;

    std::cout << "\nEnter integer number: ";
    std::cin >> f;

    std::cout << "\nCast integer to bool: "
              << std::boolalpha
              << static_cast<bool>(f)
              << std::endl;

    return 0;
}
