#include <algorithm>
#include <iostream>

struct Student
{
    const char* name;
    int marks[4];
};

void printStudent(const Student* student)
{
    std::cout << "\nStudent: " << student->name << "\nMarks:";
    for (size_t i = 0; i < 4; ++i)
    {
        std::cout << ' ' << student->marks[i];
    }
    std::cout << '\n';
}

inline float averageMark(const Student* student)
{
    int markSum = 0;
    for (size_t i = 0; i < 4; ++i)
    {
        markSum += student->marks[i];
    }
    return markSum / 4.0f;
}

void sortOnAvgMark(const Student** students, size_t studentsCount)
{
    const auto basedOnAvgMark = [](const Student* a, const Student* b) -> bool
    {
        return averageMark(a) > averageMark(b);
    };
    std::sort(students, students + studentsCount, basedOnAvgMark);
}

const Student* bestStudent(const Student** students, size_t studentsCount)
{
    sortOnAvgMark(students, studentsCount);
    return *students;
}

size_t countStudentsAboveAvgVal(const Student** students, size_t studentsCount, uint16_t avgPercent, uint16_t maxMark)
{
    const float avgVal = maxMark * avgPercent / 100.0f;
    size_t studentsAboveAvgVal = 0;
    for (size_t i = 0; i < studentsCount; ++i)
    {
        if (averageMark(students[i]) > avgVal)
        {
            studentsAboveAvgVal++;
        }
    }
    return studentsAboveAvgVal;
}

int main()
{
    /* Task 1 */
    const Student student = {
        "John Doe",
        {100, 90, 95, 90}
    };
    printStudent(&student);
    std::cout << "Average mark: " << averageMark(&student) << '\n';

    /* Task 2 */
    const Student student1 = {
        "Jane Smith",
        {90, 90, 100, 100}
    };
    const Student student2 = {
        "Mark Johnson",
        {85, 80, 70, 90}
    };
    const Student student3 = {
        "Emily Davis",
        {70, 75, 85, 75}
    };
    const Student student4 = {
        "Michael Wilson",
        {60, 90, 85, 65}
    };
    const size_t studentsCount = 5;
    const Student* students[studentsCount];
    students[0] = &student;
    students[1] = &student1;
    students[2] = &student2;
    students[3] = &student3;
    students[4] = &student4;

    /* Task 3 */
    for (size_t i = 1; i < studentsCount; ++i)
    {
        printStudent(students[i]);
        std::cout << "Average mark: " << averageMark(students[i]) << '\n';
    }
    std::cout << "\nSorting based on average mark...\n";
    sortOnAvgMark(students, studentsCount);
    for (size_t i = 0; i < studentsCount; ++i)
    {
        printStudent(students[i]);
        std::cout << "Average mark: " << averageMark(students[i]) << '\n';
    }

    /* Task 4 */
    std::cout << "\nBest student:\n";
    printStudent(bestStudent(students, studentsCount));
    std::cout << "Average mark: " << averageMark(bestStudent(students, studentsCount)) << '\n';

    /* Task 5 */
    const uint16_t avgPercent = 75;
    const uint16_t maxMark = 100;
    std::cout << "\nAmount of students with average mark above " << avgPercent << "%: "
              << countStudentsAboveAvgVal(students, studentsCount, avgPercent, maxMark) << '\n';

    return 0;
}
