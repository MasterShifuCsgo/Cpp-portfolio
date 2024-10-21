#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct student {
    std::string firstName;
    std::string lastName;
    int roll = -1; 
    float cgpa = -1.0; 
    int course = -1; 

    std::vector<std::string> details = {"", "", to_string(roll), to_string(cgpa), to_string(course)}; 
};

struct StudentDataHolder{
    vector<student> records; 
};

bool checkUniqeness(student &s, StudentDataHolder &Database, string detailName){
    
    int index{};

    if(detailName == "First Name"){
        index = 0;
    }
    if(detailName == "Last Name"){
        index = 1;
    }
    if(detailName == "Roll"){
        index = 2;
    }
    if(detailName == "CGPA"){
        index = 3;
    }
    if(detailName == "Course"){
        index = 4;
    }

    vector<int> matching {};

    for(int i{}; i < Database.records.size(); i++){
        if(Database.records[i].details[index] == s.details[index]){
            matching.push_back(i);
        }
    }

    if(matching.size() >= 2){

        cout << "\nMatching Student(s) found:\n";
        for(int i{}; i < matching.size(); i++){
            cout << "\tstudent ID: " << i << '\n';
        }
        return false;
    }

    return true;
}

void addUser(student s, StudentDataHolder &Database){
    Database.records.push_back(s);
};

void setStudentDetails(student &student){

    //first name
    cout << "Enter Your first name: ";
    cin >> student.firstName;
    //last name
    cout << "Enter Your last name: ";
    cin >> student.lastName;

    int rollNumber;
    float cgpa;
    int courseNumber;

    // Get roll number with input validation
    do {
        cout << "Enter Your Roll number: ";
        while (!(cin >> rollNumber)) {
            cout << "\nInvalid input. Please enter a valid roll number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (rollNumber < 0); // Additional validation: Roll number must be non-negative

    student.roll = rollNumber;

    // Get CGPA with input validation (same logic as before)
    do {
        cout << "Enter your CGPA: ";
        while (!(cin >> cgpa)) {
            cout << "\nInvalid input. Please enter a valid CGPA number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cgpa < 0.0f); // Additional validation: CGPA must be non-negative

    student.cgpa = cgpa;

    // Get course number with input validation
    do {
        cout << "Enter Your course number: ";
        while (!(cin >> courseNumber)) {
            cout << "\nInvalid input. Please enter a valid course number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (courseNumber < 0); // Additional validation: Course number must be non-negative

    student.course = courseNumber;
}

void printStudentDetails(student &student){

    cout << "\n------------ student Details ------------";
    cout << "\nFirst name: " << student.firstName;
    cout << "\nLast name: " << student.lastName;
    cout << "\nRoll: " << student.roll;
    cout << "\nCGPA: " << student.cgpa;
    cout << "\nCourse: " << student.course;

}

int main(){

    //Global student data holder
    StudentDataHolder Data; //student position in the list is the id of the student

    student student; //adds student to data;
    setStudentDetails(student); //asks for and sets student details.
    addUser(student, Data);
    checkUniqeness(student, Data, "Roll");

    for(int i{}; i < Data.records.size(); i++){
        printStudentDetails(Data.records[i]); //prints user details
    }

    return 0;
}
