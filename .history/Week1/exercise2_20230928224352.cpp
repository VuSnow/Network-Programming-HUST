#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Student{
    string studentID;
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
    string semester;
    double progressWeight;
    double finalWeight;
    Student* students;
    ScoreBoard* next;
};

ScoreBoard* scoreBoards = nullptr;

void addScoreBoard(){
    ScoreBoard* newScoreBoard = new ScoreBoard;
    newScoreBoard->next = scoreBoards;
    scoreBoards = newScoreBoard;

    cout << "Enter subject ID: ";
    cin >> newScoreBoard->subjectID;
    cout << "Enter subject name: ";
    cin.ignore();
    getline(cin, newScoreBoard->name);
    cout << "Enter progress weight: ";
    cin >> newScoreBoard->progressWeight;
    cout << "Enter final exam weight: ";
    cin >> newScoreBoard->finalWeight;
    cout << "Enter semester code: ";
    cin >> newScoreBoard->semester;
    cout << "Enter the number of students: ";
    int numStudents;
    cin >> numStudents;

    string fileName = newScoreBoard->subjectID + "_" + newScoreBoard->semester + ".txt";
    ofstream outFile(fileName);
    if(!outFile){
        cerr << "Error creating file: " << fileName << endl;
        return;
    }

    outFile << "SubjectID|" << newScoreBoard->subjectID << endl;
    outFile << "Subject|" << newScoreBoard->name << endl;
    outFile << "F|" << newScoreBoard->progressWeight << "|" << newScoreBoard->finalWeight << endl;
    outFile << "Semester|" << newScoreBoard->semester << endl;
    outFile << "StudentCount|" << numStudents << endl;

    newScoreBoard->students = nullptr;
    for (int i = 0; i < numStudents; ++i) {
        Student* newStudent = new Student;
        cout << "Enter student ID: ";
        cin >> newStudent->studentID;
        cout << "Enter first name: ";
        cin.ignore();
        getline(cin,newStudent->firstName );
        // cin >> newStudent->firstName;
        cout << "Enter last name: ";
        cin >> newStudent->lastName;
        cout << "Enter progress mark: ";
        cin >> newStudent->progress;
        cout << "Enter final exam mark: ";
        cin >> newStudent->finalExam;

        // Calculate grade
        double totalMark = (newStudent->progress * newScoreBoard->progressWeight/100 +
                            newStudent->finalExam * newScoreBoard->finalWeight/100);
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

        newStudent->next = newScoreBoard->students;
        newScoreBoard->students = newStudent;
    }

    cout << "Scoreboard added successfully!" << endl;
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