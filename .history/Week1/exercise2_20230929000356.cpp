#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <iomanip>

using namespace std;

struct Student{
    string studentID;
    string firstName;
    string lastName;
    double progress;
    double finalExam;
    double totalMark;
    char grade;
    Student* next;
};

struct ScoreBoard{
    string subjectID;
    string name;
    string semester;
    double progressWeight;
    double finalWeight;
    int numStudents;
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
    cin >> newScoreBoard->numStudents;

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
    outFile << "StudentCount|" << newScoreBoard->numStudents << endl;

    newScoreBoard->students = nullptr;
    for (int i = 0; i < newScoreBoard->numStudents; ++i) {
        Student* newStudent = new Student;
        cout << "Student " << i+1 << "'s information" << endl;
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
        newStudent->totalMark = (newStudent->progress * newScoreBoard->progressWeight/100 +
                            newStudent->finalExam * newScoreBoard->finalWeight/100);
        if (newStudent->totalMark >= 8.5)
            newStudent->grade = 'A';
        else if (newStudent->totalMark >= 7.0)
            newStudent->grade = 'B';
        else if (newStudent->totalMark >= 5.5)
            newStudent->grade = 'C';
        else if (newStudent->totalMark >= 4.0)
            newStudent->grade = 'D';
        else
            newStudent->grade = 'F';

        newStudent->next = newScoreBoard->students;
        newScoreBoard->students = newStudent;

        outFile << "S|" << newStudent->studentID << "|" << newStudent->firstName << "\t\t|" << newStudent->lastName << "\t\t|" << fixed << setprecision(1) << newStudent->progress << "\t|" << newStudent->finalExam << "\t|" << newStudent->grade << "\t|" << endl;
    }

    cout << "Scoreboard added successfully!" << endl;
}

void addScore(){

}

void removeScore(){
    string subjectID, semesterID, studentID;
    cout << "Enter subject ID: ";
    cin >> subjectID;
    cout << "Enter semester ID: ";
    cin >> semesterID;
    cout << "Enter student ID: ";
    cin >> studentID;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID && currentScoreBoard->semester == semesterID) {
            // delete students from files
            string fileName = currentScoreBoard->subjectID + "_" + currentScoreBoard->semester + ".txt";
            ifstream inFile(fileName);
            if (!inFile) {
                std::cerr << "Error opening file: " << fileName << std::endl;
                return;
            }
            vector<string> fileLines;
            string line;
            while(getline(inFile, line)){
                fileLines.push_back(line);
            }
            inFile.close();
            bool studentFound = false;
            for (size_t i = 0; i < fileLines.size(); ++i) {
                std::string line = fileLines[i];
                if (line.find(studentID) != std::string::npos) {
                    // Xóa thông tin sinh viên bằng cách bỏ qua dòng này
                    fileLines.erase(fileLines.begin() + i);
                    studentFound = true;
                    break;
                }
            }
            if (!studentFound) {
                std::cout << "Student with ID " << studentID << " not found in the file." << std::endl;
                return;
            }
            
            std::ofstream outFile(fileName);
            if (!outFile) {
                std::cerr << "Error opening file for writing: " << fileName << std::endl;
                return;
            }

            for (const std::string& line : fileLines) {
                outFile << line << std::endl;
            }

            outFile.close();
            std::cout << "Student with ID " << studentID << " removed from the file." << std::endl;

            // delete students from data
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

void searchScore(){
    string subjectID, semesterID, studentID;
    cout << "Enter subject ID: ";
    cin >> subjectID;
    cout << "Enter semester ID: ";
    cin >> semesterID;
    cout << "Enter student ID: ";
    cin >> studentID;

    cout << endl << endl;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID && currentScoreBoard->semester == semesterID) {
            Student* currentStudent = currentScoreBoard->students;

            while (currentStudent != nullptr) {
                if (currentStudent->studentID == studentID) {
                    cout << "Student ID: " << currentStudent->studentID << endl;
                    cout << "Name: " << currentStudent->firstName << " " << currentStudent->lastName << endl;
                    cout << "Progress Mark: " << currentStudent->progress << endl;
                    cout << "Final Exam Mark: " << currentStudent->finalExam << endl;
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

string searchStudentFromMark(double totalMark, string subjectID, string semester){
    Student* foundStudent;
    ScoreBoard* currentScoreBoard = scoreBoards;
    while(currentScoreBoard != nullptr){
        if(currentScoreBoard->subjectID == subjectID && currentScoreBoard->semester == semester){
            Student* currentStudent = currentScoreBoard->students;

            while(currentStudent != nullptr){
                if(currentStudent->totalMark == totalMark){
                    foundStudent == currentStudent;
                }
            }
        }
    }
    return foundStudent->firstName + " " + foundStudent->lastName;
}

void displayScoreBoard(){
    string subjectID, semesterID;
    cout << "Enter subject ID: ";
    cin >> subjectID;
    cout << "Enter semester ID: ";
    cin >> semesterID;

    ScoreBoard* currentScoreBoard = scoreBoards;
    while (currentScoreBoard != nullptr) {
        if (currentScoreBoard->subjectID == subjectID && currentScoreBoard->semester == semesterID) {
            // print score board
            cout << "Score Board of " << currentScoreBoard->subjectID << ":"; 
            string fileName = currentScoreBoard->subjectID + "_" + currentScoreBoard->semester + ".txt";
            ifstream inFile(fileName);
            if(!inFile){
                cerr << "Error opening file: " << fileName << endl;
                return;
            }
            string line;
            while(getline(inFile, line)){
                cout << line << endl;
            }
            inFile.close();

            // Calculate statistics
            int numStudents = 0;
            double totalMarks = 0;
            int numA = 0, numB = 0, numC = 0, numD = 0, numF = 0;
            int maxMark = 0; 
            int minMark = 10;

            Student* currentStudent = currentScoreBoard->students;

            while (currentStudent != nullptr) {
                numStudents++;
                totalMarks += (currentStudent->progress * currentScoreBoard->progressWeight /100 +
                               currentStudent->finalExam * currentScoreBoard->finalWeight /100);
                
                if(currentStudent->totalMark > maxMark){
                    maxMark = currentStudent->totalMark;
                }
                if(currentStudent->totalMark < minMark){
                    minMark = currentStudent->totalMark;
                }
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
            // string studentMaxName = searchStudentFromMark(maxMark,subjectID, semesterID);
            // string studentMinName = searchStudentFromMark(minMark, subjectID, semesterID);

            // cout << "The student with the highest mark is: " << studentMaxName << endl;
            // cout << "The student with the lowest mark is: " << studentMinName << endl;
            cout << "The average mark is: " << averageMark << endl;
            cout << "A: " << numA << endl;
            cout << "B: " << numB << endl;
            cout << "C: " << numC << endl;
            cout << "D: " << numD << endl;
            cout << "F: " << numF << endl;

            cout << "Score Board of " << currentScoreBoard->subjectID << ":"; 
            return;
        }
        currentScoreBoard = currentScoreBoard->next;
    }

    cout << "Scoreboard not found for the given subject ID." << endl;
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