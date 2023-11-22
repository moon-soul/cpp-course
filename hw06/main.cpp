#include <iostream>
#include <string>
#include <cctype>

int main()
{
    /* Task 1 */
    int a1 = 0;
    int d = 0;
    int lastNum = 0;

    std::cout << "Enter a1: ";
    std::cin >> a1;
    std::cout << "Enter d: ";
    std::cin >> d;
    std::cout << "Enter number of last member: ";
    std::cin >> lastNum;

    if (lastNum > 0)
    {
        /* Solution 1 */
        std::cout << "\nArithmetic progression: ";
        std::cout << a1; // To avoid unnecessary addition to variable "AP" on the last iteration
        int AP = a1; // i = 0
        for (int i = 1; i < lastNum; ++i)
        {
            AP += d;
            std::cout << ' ' << AP;
        }
        std::cout << std::endl;

        /* Solution 2 */
        std::cout << "\nArithmetic progression: ";
        for (int i = 0; i < lastNum; ++i)
        {
            AP = a1 + i * d;
            std::cout << AP << ' ';
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "\nNumber of last member should be 1 or greater." << std::endl;
    }

    /* Task 2 */
    int fibNum = 0;

    std::cout << "\nEnter Fibonacci element number: ";
    std::cin >> fibNum;

    if (fibNum > 0)
    {
        int fibVal = 1; // Fib(1); i = 0
        for (int i = 1, tmp = 0, prev = 0; i < fibNum; ++i)
        {
            tmp = fibVal;
            fibVal += prev;
            prev = tmp;
        }
        std::cout << "\nFibonacci element number " << fibNum << ": " << fibVal;
    }
    else if (fibNum == 0)
    {
        std::cout << "\nFibonacci element number 0: 0";
    }
    else
    {
        std::cout << "\nFibonacci element number should be 0 or greater.";
    }
    std::cout << std::endl;

    /* Task 3 */
    int n = 0;

    std::cout << "\nEnter n: ";
    std::cin >> n;

    if (n > 0)
    {
        int factorial = 1; // 1!; i = 0
        for (int i = 1; i <= n; ++i)
        {
            factorial *= i;
        }
        std::cout << '\n' << n << "! (factorial): " << factorial;
    }
    else if (n == 0)
    {
        std::cout << "\n0! (factorial): 1";
    }
    else
    {
        std::cout << "\nn should be 0 or greater.";
    }
    std::cout << std::endl;

    /* Task 4 */
    char triangleFiller = '*';
    int triangleSize = 0;

    std::cout << "\nEnter filler character: ";
    std::cin >> triangleFiller;
    std::cout << "Enter triangle size: ";
    std::cin >> triangleSize;

    if (triangleSize > 1)
    {
        /* A */
        /* Solution 1 */
        for (int i = triangleSize; i > 0; --i)
        {
            std::cout << '\n' << std::string(i, triangleFiller);
        }
        std::cout << std::endl;

        /* Solution 2 */
        for (int i = 0; i < triangleSize; ++i)
        {
            std::cout << '\n';
            for (int j = i; j < triangleSize; ++j)
            {
                std::cout << triangleFiller;
            }
        }
        std::cout << std::endl;

        /* B */
        /* Solution 1 */
        for (int i = 1; i <= triangleSize; ++i)
        {
            std::cout << '\n' << std::string(i, triangleFiller);
        }
        std::cout << std::endl;

        /* Solution 2 */
        for (int i = 0; i < triangleSize; ++i)
        {
            std::cout << '\n';
            for (int j = 0; j <= i; ++j)
            {
                std::cout << triangleFiller;
            }
        }
        std::cout << std::endl;

        /* E */
        for (int i = 0, numToPrint = 0; i < triangleSize; ++i)
        {
            std::cout << '\n';
            numToPrint = i & 1; // Determine whether the value of "i" is even or odd
            for (int j = 0; j <= i; ++j)
            {
                numToPrint ^= 1; // Flip 0 to 1 and vice versa
                std::cout << numToPrint;
            }
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "\nTriangle size should be 2 or greater." << std::endl;
    }

    /* Task 4 */
    char quadrangleFiller = '*';
    int quadrangleRows = 0;
    int quadrangleColumns = 0;

    std::cout << "\nEnter filler character: ";
    std::cin >> quadrangleFiller;
    std::cout << "Enter number of rows: ";
    std::cin >> quadrangleRows;
    std::cout << "Enter number of columns: ";
    std::cin >> quadrangleColumns;

    if (quadrangleRows > 1 && quadrangleColumns > 1)
    {
        /* C */
        /* Solution 1 */
        for (int i = 0; i < quadrangleRows; ++i)
        {
            std::cout << '\n' << std::string(quadrangleColumns, quadrangleFiller);
        }
        std::cout << std::endl;

        /* Solution 2 */
        for (int i = 0; i < quadrangleRows; ++i)
        {
            std::cout << '\n';
            for (int j = 0; j < quadrangleColumns; ++j)
            {
                std::cout << quadrangleFiller;
            }
        }
        std::cout << std::endl;

        /* D */
        /* Solution 1 */
        for (int i = 0; i < quadrangleRows; ++i)
        {
            std::cout << '\n' << std::string(i, ' ')
                      << std::string(quadrangleColumns, quadrangleFiller);
        }
        std::cout << std::endl;

        /* Solution 2 */
        for (int i = 0; i < quadrangleRows; ++i)
        {
            std::cout << '\n';
            for (int offsetSpaces = 0; offsetSpaces < i; ++offsetSpaces)
            {
                std::cout << ' ';
            }
            for (int j = 0; j < quadrangleColumns; ++j)
            {
                std::cout << quadrangleFiller;
            }
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "\nMinimal quadrangle size is 2x2." << std::endl;
    }

    /* Task 5 */
    char c = '\0';
    int sum = 0;

    while (true)
    {
        std::cout << "\nEnter character: ";
        std::cin >> c;
        if (islower(c))
        {
            std::cout << "\nOutput: " << static_cast<char>(toupper(c)) << '\n';
        }
        else if (isupper(c))
        {
            std::cout << "\nOutput: " << c << '\n';
        }
        else if (isdigit(c))
        {
            sum += c - '0';
            std::cout << "\nSum: " << sum << '\n';
        }
        else if (c == '.')
        {
            std::cout << "\nExiting..." << std::endl;
            return 0;
            // break;
        }
        else
        {
            std::cout << "\nCannot process symbol: " << c << '\n';
            continue;
        }
    }

    // return 0;
}
