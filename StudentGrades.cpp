// Student Grades Project
// CSC 222
// This program reads student grades and uses dynamic memory
// to store student records and test scores.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Student
{
    string lastName;
    int studentID;
    double* scores;
    double average;
    char letterGrade;
};

int main()
{
    ifstream inputFile("student_data.txt");

    if (!inputFile)
    {
        cout << "Error: Could not open student_data.txt" << endl;
        return 1;
    }

    int studentCount;
    int testCount;

    if (!(inputFile >> studentCount >> testCount) ||
        studentCount <= 0 || testCount <= 0)
    {
        cout << "Error: Invalid file header." << endl;
        return 1;
    }

    Student* students = new Student[studentCount];

    for (int i = 0; i < studentCount; i++)
    {
        students[i].scores = nullptr;
    }

    cout << "Number of students: " << studentCount << endl;
    cout << "Number of tests: " << testCount << endl;

    delete[] students;
    students = nullptr;

    inputFile.close();

    return 0;
}