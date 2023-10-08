#include<iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student{
    string studentID;
    string firstName;
    string lastName;
    float progessMark;
    float finalExamMark;
    char grade;
    Student* next;
};

struct ScoreBoard{
    string subjectID;
    string subjectName;
    double progessWeight;
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
}
ScoreBoard* scoreBoards = nullptr;
int main(){

}