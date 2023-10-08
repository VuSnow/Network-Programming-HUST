#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Student{
    string firstName;
    string lastName;
    double progress;
    double finalExam;
    char grade;
    Student* next;
};

struct ScoreBoard{
    string subjectID;
    string name;
    double progressWeight;
    double finalWeight;
    Student* students;
    ScoreBoard* next;
};

ScoreBoard* scoreBoard = nullptr;

void addScoreBoard(){

}

void addScore(){

}

void removeScore(){

}

void searchScore(){

}

void displayScoreBoard(){

}

int main(){
    int choice;
    do {
        cout << "Learning Management System" << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Add a new score board" << endl;
        cout << "2. Add score" << endl;
        cout << "3. Remove score" << endl;
        cout << "4. Search score" << endl;
        cout << "5. Display score board and score report" << endl;
        cout << "Your choice (1-5, other to quit): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addScoreBoard();
                break;
            case 2:
                addScore();
                break;
            case 3:
                removeScore();
                break;
            case 4:
                searchScore();
                break;
            case 5:
                displayScoreBoard();
                break;
            default:
                cout << "Goodbye!" << endl;
                break;
        }
    } while (choice >= 1 && choice <= 5);

    // Clean up memory (free allocated nodes)

    return 0;
}