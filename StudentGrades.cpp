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
    int studentID = 0;
    double* scores = nullptr;
    double average = 0.0;
    char letterGrade = 'F';
};

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
        double average = students[i].average;

        if (average >= 90)
            students[i].letterGrade = 'A';
        else if (average >= 80)
            students[i].letterGrade = 'B';
        else if (average >= 70)
            students[i].letterGrade = 'C';
        else if (average >= 60)
            students[i].letterGrade = 'D';
        else
            students[i].letterGrade = 'F';
    }
}

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

    bool dataValid = true;

    for (int i = 0; i < studentCount; i++)
    {
        if (!(inputFile >> students[i].lastName >> students[i].studentID))
        {
            dataValid = false;
            break;
        }

        students[i].scores = new double[testCount];

        for (int j = 0; j < testCount; j++)
        {
            if (!(inputFile >> students[i].scores[j]))
            {
                dataValid = false;
                break;
            }
        }

        if (!dataValid)
            break;
    }

    if (!dataValid)
    {
        cout << "Error: Invalid student data." << endl;

        for (int i = 0; i < studentCount; i++)
        {
            delete[] students[i].scores;
        }

        delete[] students;
        inputFile.close();
        return 1;
    }

    calculateAverages(students, studentCount, testCount);
    assignLetterGrades(students, studentCount); 

    cout << "Number of students: " << studentCount << endl;
    cout << "Number of tests: " << testCount << endl;

    for (int i = 0; i < studentCount; i++)
    {
        cout << students[i].lastName << " "
            << students[i].studentID << ": ";

        for (int j = 0; j < testCount; j++)
        {
            cout << students[i].scores[j] << " ";
        }

        cout << " Average: " << fixed << setprecision(2)
            << students[i].average
            << " Grade: " << students[i].letterGrade << endl;
    }

    for (int i = 0; i < studentCount; i++)
    {
        delete[] students[i].scores;
        students[i].scores = nullptr;
    }

    delete[] students;
    students = nullptr;

    inputFile.close();

    return 0;
}