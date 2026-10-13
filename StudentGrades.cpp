// Student Grades Project - CSC 222

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Student
{
    string lastName;
    int studentID = 0;
    double* scores = nullptr;
    double average = 0.0;
    char letterGrade = 'F';
};

void releaseMemory(Student*& students, int studentCount)
{
    if (students == nullptr)
        return;

    for (int i = 0; i < studentCount; i++)
    {
        delete[] students[i].scores;
        students[i].scores = nullptr;
    }

    delete[] students;
    students = nullptr;
}

bool readGradeData(const string& fileName, Student*& students,
    int& studentCount, int& testCount)
{
    ifstream file(fileName);

    if (!file)
    {
        cout << "Error: Could not open " << fileName << endl;
        return false;
    }

    if (!(file >> studentCount >> testCount) ||
        studentCount <= 0 || testCount <= 0)
    {
        cout << "Error: Invalid file header." << endl;
        return false;
    }

    students = new Student[studentCount];

    for (int i = 0; i < studentCount; i++)
    {
        if (!(file >> students[i].lastName >> students[i].studentID))
        {
            cout << "Error: Invalid student data." << endl;
            releaseMemory(students, studentCount);
            return false;
        }

        students[i].scores = new double[testCount];

        for (int j = 0; j < testCount; j++)
        {
            if (!(file >> students[i].scores[j]))
            {
                cout << "Error: Missing or invalid test score." << endl;
                releaseMemory(students, studentCount);
                return false;
            }
        }
    }

    return true;
}

void calculateAverages(Student* students, int studentCount, int testCount)
{
    for (int i = 0; i < studentCount; i++)
    {
        double total = 0.0;

        for (int j = 0; j < testCount; j++)
        {
            total += students[i].scores[j];
        }

        students[i].average = total / testCount;
    }
}

void assignLetterGrades(Student* students, int studentCount)
{
    for (int i = 0; i < studentCount; i++)
    {
        double avg = students[i].average;

        if (avg >= 90)
            students[i].letterGrade = 'A';
        else if (avg >= 80)
            students[i].letterGrade = 'B';
        else if (avg >= 70)
            students[i].letterGrade = 'C';
        else if (avg >= 60)
            students[i].letterGrade = 'D';
        else
            students[i].letterGrade = 'F';
    }
}

void displayReport(const Student* students, int studentCount, int testCount)
{
    cout << "Student Grades Report\n";
    cout << "Students: " << studentCount << "  Tests: " << testCount << "\n\n";

    cout << left << setw(15) << "Last Name" << setw(10) << "ID";

    for (int j = 0; j < testCount; j++)
    {
        cout << right << setw(9) << ("Test " + to_string(j + 1));
    }

    cout << setw(11) << "Average" << setw(8) << "Grade" << '\n';
    cout << string(25 + 9 * testCount + 19, '-') << '\n';

    cout << fixed << setprecision(2);

    for (int i = 0; i < studentCount; i++)
    {
        cout << left << setw(15) << students[i].lastName
            << setw(10) << students[i].studentID;

        for (int j = 0; j < testCount; j++)
        {
            cout << right << setw(9) << students[i].scores[j];
        }

        cout << setw(11) << students[i].average
            << setw(8) << students[i].letterGrade << '\n';
    }
}

int main()
{
    Student* students = nullptr;
    int studentCount = 0;
    int testCount = 0;

    if (!readGradeData("student_data.txt", students, studentCount, testCount))
        return 1;

    calculateAverages(students, studentCount, testCount);
    assignLetterGrades(students, studentCount);
    displayReport(students, studentCount, testCount);

    releaseMemory(students, studentCount);

    return 0;
}
