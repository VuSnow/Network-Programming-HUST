#include<iostream>
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

ScoreBoard* scoreBoards = nullptr;
int main(){

}