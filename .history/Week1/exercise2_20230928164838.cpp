#include<iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student{
    string studentID;
    string firstName;
    string lastName;
    float progressMark;
    float finalExamMark;
    char grade;
    Student* next;
};

struct ScoreBoard{
    string subjectID;
    string subjectName;
    double progressWeight;
    double finalExamWeight;
    Student* student;
    ScoreBoard* next;
};

void addNewScoreBoard(){
    ScoreBoard* newScoreBoard = new ScoreBoard;
    newScoreBoard->next = scoreBoards;
    scoreBoards = newScoreBoard;

    cout << "Enter subject ID: ";
    cin >> newScoreBoard->subjectID;
    cout << "Enter subject name: ";
    cin.ignore();
    getline(cin,newScoreBoard->subjectName);
    cout << "Enter progress weight: ";
    cin >> newScoreBoard->progressWeight;
    cout << "Enter final exam weight: ";
    cin >> newScoreBoard->finalExamWeight;
    cout << "Enter the number of students: ";
    int numStudents;
    cin >> numStudents;

    newScoreBoard->student = nullptr;
    for (int i = 0; i < numStudents; ++i) {
        Student* newStudent = new Student;
        cout << "Enter student ID: ";
        cin >> newStudent->studentID;
        cout << "Enter first name: ";
        cin >> newStudent->firstName;
        cout << "Enter last name: ";
        cin >> newStudent->lastName;
        cout << "Enter progress mark: ";
        cin >> newStudent->progressMark;
        cout << "Enter final exam mark: ";
        cin >> newStudent->finalExamMark;

        // Calculate grade
        double totalMark = (newStudent->progressMark * newScoreBoard->progressWeight +
                            newStudent->finalExamMark * newScoreBoard->finalExamWeight);
        if (totalMark >= 8.5)
            newStudent->grade = 'A';
        else if (totalMark >= 7.0)
            newStudent->grade = 'B';
        else if (totalMark >= 5.5)
            newStudent->grade = 'C';
        else if (totalMark >= 4.0)
            newStudent->grade = 'D';
        else
            newStudent->grade = 'F';

        newStudent->next = newScoreBoard->student;
        newScoreBoard->student = newStudent;
    }

    cout << "Scoreboard added successfully!" << endl;
}
ScoreBoard* scoreBoards = nullptr;
int main(){

}