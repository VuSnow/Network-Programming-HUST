#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string studentID;
    string firstName;
    string lastName;
    double progressMark;
    double finalExamMark;
    char grade;
    Student* next;
};

struct ScoreBoard {
    string subjectID;
    string subjectName;
    double progressWeight;
    double finalExamWeight;
    Student* students;
    ScoreBoard* next;
};

ScoreBoard* scoreBoards = nullptr;

void addScoreBoard() {
    ScoreBoard* newScoreBoard = new ScoreBoard;
    newScoreBoard->next = scoreBoards;
    scoreBoards = newScoreBoard;

    cout << "Enter subject ID: ";
    cin >> newScoreBoard->subjectID;
    cout << "Enter subject name: ";
    cin.ignore();
    getline(cin, newScoreBoard->subjectName);
    cout << "Enter progress weight: ";
    cin >> newScoreBoard->progressWeight;
    cout << "Enter final exam weight: ";
    cin >> newScoreBoard->finalExamWeight;
    cout << "Enter the number of students: ";
    int numStudents;
    cin >> numStudents;

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

        newStudent->next = newScoreBoard->students;
        newScoreBoard->students = newStudent;
    }

    cout << "Scoreboard added successfully!" << endl;
}

void addScore() {
    string subjectID, semesterID;
    cout << "Enter subject ID: ";
    cin >> subjectID;
    cout << "Enter semester ID: ";
    cin >> semesterID;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID) {
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
            double totalMark = (newStudent->progressMark * currentScoreBoard->progressWeight +
                                newStudent->finalExamMark * currentScoreBoard->finalExamWeight);
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

            newStudent->next = currentScoreBoard->students;
            currentScoreBoard->students = newStudent;

            cout << "Score added successfully!" << endl;
            return;
        }
        currentScoreBoard = currentScoreBoard->next;
    }

    cout << "Scoreboard not found for the given subject ID." << endl;
}

void removeScore() {
    string subjectID, semesterID, studentID;
    cout << "Enter subject ID: ";
    cin >> subjectID;
    cout << "Enter semester ID: ";
    cin >> semesterID;
    cout << "Enter student ID: ";
    cin >> studentID;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID) {
            Student* prevStudent = nullptr;
            Student* currentStudent = currentScoreBoard->students;

            while (currentStudent != nullptr) {
                if (currentStudent->studentID == studentID) {
                    if (prevStudent != nullptr) {
                        prevStudent->next = currentStudent->next;
                    } else {
                        currentScoreBoard->students = currentStudent->next;
                    }
                    delete currentStudent;
                    cout << "Score removed successfully!" << endl;
                    return;
                }
                prevStudent = currentStudent;
                currentStudent = currentStudent->next;
            }

            cout << "Student not found in the given subject." << endl;
            return;
        }
        currentScoreBoard = currentScoreBoard->next;
    }

    cout << "Scoreboard not found for the given subject ID." << endl;
}

void searchScore() {
    string subjectID, semesterID, studentID;
    cout << "Enter subject ID: ";
    cin >> subjectID;
    cout << "Enter semester ID: ";
    cin >> semesterID;
    cout << "Enter student ID: ";
    cin >> studentID;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID) {
            Student* currentStudent = currentScoreBoard->students;

            while (currentStudent != nullptr) {
                if (currentStudent->studentID == studentID) {
                    cout << "Student ID: " << currentStudent->studentID << endl;
                    cout << "First Name: " << currentStudent->firstName << endl;
                    cout << "Last Name: " << currentStudent->lastName << endl;
                    cout << "Progress Mark: " << currentStudent->progressMark << endl;
                    cout << "Final Exam Mark: " << currentStudent->finalExamMark << endl;
                    cout << "Grade: " << currentStudent->grade << endl;
                    return;
                }
                currentStudent = currentStudent->next;
            }

            cout << "Student not found in the given subject." << endl;
            return;
        }
        currentScoreBoard = currentScoreBoard->next;
    }

    cout << "Scoreboard not found for the given subject ID." << endl;
}

void displayScoreBoard() {
    string subjectID;
    cout << "Enter subject ID: ";
    cin >> subjectID;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID) {
            // Calculate statistics
            int numStudents = 0;
            double totalMarks = 0;
            int numA = 0, numB = 0, numC = 0, numD = 0, numF = 0;

            Student* currentStudent = currentScoreBoard->students;
            while (currentStudent != nullptr) {
                numStudents++;
                totalMarks += (currentStudent->progressMark * currentScoreBoard->progressWeight +
                               currentStudent->finalExamMark * currentScoreBoard->finalExamWeight);

                switch (currentStudent->grade) {
                    case 'A':
                        numA++;
                        break;
                    case 'B':
                        numB++;
                        break;
                    case 'C':
                        numC++;
                        break;
                    case 'D':
                        numD++;
                        break;
                    case 'F':
                        numF++;
                        break;
                }

                currentStudent = currentStudent->next;
            }

            double averageMark = totalMarks / numStudents;

            cout << "The student with the highest mark is: TODO" << endl;
            cout << "The student with the lowest mark is: TODO" << endl;
            cout << "The average mark is: " << averageMark << endl;
            cout << "A: " << numA << endl;
            cout << "B: " << numB << endl;
            cout << "C: " << numC << endl;
            cout << "D: " << numD << endl;
            cout << "F: " << numF << endl;

            return;
        }
        currentScoreBoard = currentScoreBoard->next;
    }

    cout << "Scoreboard not found for the given subject ID." << endl;
}

int main() {
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
