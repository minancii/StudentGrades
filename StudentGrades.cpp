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
    cout << "Student Grades Project" << endl;

    return 0;
}