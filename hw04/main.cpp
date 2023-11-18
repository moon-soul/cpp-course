#include <iostream>

int main()
{
    /* Task 1 */
    int a = 0;
    int b = 0;
    int c = 0;
    int maxOfThree = 0;

    std::cout << "Enter first number: ";
    std::cin >> a;
    std::cout << "Enter second number: ";
    std::cin >> b;
    std::cout << "Enter third number: ";
    std::cin >> c;

    /* Solution 1 */
    maxOfThree = a > b ? a : b;
    maxOfThree = c > maxOfThree ? c : maxOfThree;
    std::cout << "\nMax of three numbers: " << maxOfThree << std::endl;

    /* Solution 2 */
    maxOfThree = a;
    if (b > maxOfThree) maxOfThree = b;
    if (c > maxOfThree) maxOfThree = c;
    std::cout << "\nMax of three numbers: " << maxOfThree << std::endl;

    /* Solution 3 */
    std::cout << "\nMax of three numbers: ";
    if (a > b && a > c)
        std::cout << a;
    else if (b > a && b > c)
        std::cout << b;
    else
        std::cout << c;
    std::cout << std::endl;

    /* Task 2 */
    int x = 0;
    int y = 0;

    std::cout << "\nEnter first number: ";
    std::cin >> x;
    std::cout << "Enter second number: ";
    std::cin >> y;

    const int minOfTwo = x < y ? x : y;
    std::cout << "\nMin of two numbers: " << minOfTwo << std::endl;

    /* Task 3 */
    int num = 0;

    std::cout << "\nEnter number: ";
    std::cin >> num;

    /* Solution 1 */
    const bool isDividable = ((num % 5 == 0) && (num % 11 == 0));
    std::cout << "\nNumber " << num << " is dividable by 5 and 11 simultaneously: "
              << std::boolalpha << isDividable << '.' << std::endl;
    
    /* Solution 2 */
    std::cout << "\nNumber " << num;
    if ((num % 5 == 0) && (num % 11 == 0))
        std::cout << " is";
    else
        std::cout << " is not";
    std::cout << " dividable by 5 and 11 simultaneously." << std::endl;

    /* Task 4 */
    int A = 0;
    int B = 0;
    int C = 0;

    std::cout << "\nEnter first angle: ";
    std::cin >> A;
    std::cout << "Enter second angle: ";
    std::cin >> B;
    std::cout << "Enter third angle: ";
    std::cin >> C;

    const bool areAnglesPositive = A > 0 && B > 0 && C > 0;
    const bool isTriangleDegree = (A + B + C) == 180;

    /* Solution 1 */
    const bool isTriangle = areAnglesPositive && isTriangleDegree;
    std::cout << "\nTriangle exists: " << std::boolalpha << isTriangle << '.' << std::endl;

    /* Solution 2 */
    if (areAnglesPositive && isTriangleDegree)
        std::cout << "\nTriangle exists.";
    else
        std::cout << "\nTriangle does not exist.";
    std::cout << std::endl;

    /* Task 5 */
    int choice = 0;
    enum class Month
    {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    std::cout << "\nEnter month number from 1 to 12: ";
    std::cin >> choice;

    const Month month = static_cast<Month>(choice);
    std::cout << "\nResult: ";
    switch (month)
    {
    case Month::January:
        std::cout << "January";
        break;
    case Month::February:
        std::cout << "February";
        break;
    case Month::March:
        std::cout << "March";
        break;
    case Month::April:
        std::cout << "April";
        break;
    case Month::May:
        std::cout << "May";
        break;
    case Month::June:
        std::cout << "June";
        break;
    case Month::July:
        std::cout << "July";
        break;
    case Month::August:
        std::cout << "August";
        break;
    case Month::September:
        std::cout << "September";
        break;
    case Month::October:
        std::cout << "October";
        break;
    case Month::November:
        std::cout << "November";
        break;
    case Month::December:
        std::cout << "December";
        break;
    default:
        std::cout << "Wrong input";
        break;
    }
    std::cout << '.' << std::endl;

    /* Task 6 */
    int n = 0;

    std::cout << "\nEnter month number from 1 to 12: ";
    std::cin >> n;

    std::cout << "\nResult: ";
    switch (n)
    {
    case 12:
    case 1:
    case 2:
        std::cout << "Winter";
        break;
    case 3:
    case 4:
    case 5:
        std::cout << "Spring";
        break;
    case 6:
    case 7:
    case 8:
        std::cout << "Summer";
        break;
    case 9:
    case 10:
    case 11:
        std::cout << "Autumn";
        break;
    default:
        std::cout << "Wrong input";
        break;
    }
    std::cout << '.' << std::endl;

    return 0;
}
