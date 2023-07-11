#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// Exception class for invalid fee amount
class InvalidFeeException : public exception {
public:
 const char* what() const throw() {
 return "Invalid changes!";
 }
};
// Base class for students
class Student {
public:
 string name;
 int rollNo;
 int standard;
 float fees;

 // Default constructor
 Student() {}
 // Parameterized constructor
 Student(string n, int r, int s, float f) : name(n), rollNo(r),
standard(s), fees(f) {}
 // Virtual function to calculate total fees
 virtual float calculateFees() {
 return fees;
 }

 int getRollNo() {
 return rollNo;
 }
 // Friend class for accessing private data members
 friend class SchoolFeeCollection;
 // Operator overloading for comparing students
 bool operator < (const Student& s) {
 return rollNo < s.rollNo;
 }
};
// Intermediate class for regular students
class RegularStudent : public Student {
protected:
 float discount;
public:
 // Default constructor
 RegularStudent() {}
 // Parameterized constructor
 RegularStudent(string n, int r, int s, float f, float d) :
Student(n, r, s, f), discount(d) {}
 // Method overriding to calculate total fees with discount
 float calculateFees() override {
 return fees - (fees * discount / 100);
 }
};
// Derived class for scholarship students
class ScholarshipStudent : public Student {
protected:
 float scholarshipAmount;
public:
 // Default constructor
 ScholarshipStudent() {}
 // Parameterized constructor
 ScholarshipStudent(string n, int r, int s, float f, float sa) :
Student(n, r, s, f), scholarshipAmount(sa) {}
 // Method overriding to calculate total fees with scholarship
 float calculateFees() override {
 return fees - scholarshipAmount;
 }
};
// Collection class for managing school fees
class SchoolFeeCollection {
public:
    int numStudents;
    Student** students;

    // Default constructor
    SchoolFeeCollection() {
        numStudents = 0;
        students = new Student*[100]; // allocate initial memory for 100 students
    }

    // Parameterized constructor
    SchoolFeeCollection(Student** s, int n) {
        numStudents = n;
        students = new Student*[numStudents]; // allocate memory for the given number of students
        for (int i = 0; i < numStudents; i++) {
            students[i] = s[i];
        }
    }


 // Inline function to display student details
 inline void displayStudentDetails(Student* s) {
 cout << "Name: " << s->name << endl;
 cout << "Roll No.: " << s->rollNo << endl;
 cout << "Standard: " << s->standard << endl;
 cout << "Fees: " << s->fees << endl;
 }
 // Function to display all students and their fees
 void displayAllStudents() {
 for (int i = 0; i < numStudents; i++) {
 cout << "Student " << i+1 << ":" << endl;
 displayStudentDetails(students[i]);
 cout << "Total fees: " << students[i]->calculateFees() << endl;
 }
 }
 // Function to calculate total fees for all students
 float calculateTotalFees() {
 float total = 0;
 for (int i = 0; i < numStudents; i++) {
 total += students[i]->calculateFees();
 }
 return total;
 }
 // Function to find a student by roll number
 Student* findStudentByRollNo(int rollNo) {
 for (int i = 0; i < numStudents; i++) {
 if (students[i]->rollNo == rollNo) {
 return students[i];
 }
 }
 return NULL;
 }
 // Function to add a new regular student
 void addRegularStudent(string name, int rollNo, int standard,
float fees, float discount) {
 RegularStudent* rs = new RegularStudent(name, rollNo,
standard, fees, discount);
 students[numStudents++] = rs;
 }
 // Function to add a new scholarship student
 void addScholarshipStudent(string name, int rollNo, int
standard, float fees, float scholarshipAmount) {
 ScholarshipStudent* ss = new ScholarshipStudent(name,
rollNo, standard, fees, scholarshipAmount);
 students[numStudents++] = ss;
 }
 // Function to delete a student by roll number
 bool deleteStudent(int rollNo) {
 // Find index of student with given roll no.
 int index = -1;
 for (int i = 0; i < numStudents; i++) {
 if (students[i]->rollNo) {
 index = i;
 break;
 }
 }
 // If student found, delete and shift remaining elements
 if (index != -1) {
 delete students[index];
 for (int i = index; i < numStudents - 1; i++) {
 students[i] = students[i + 1];
 }
 students[numStudents - 1] = NULL;
 numStudents--;
 return true;
 }
 return false;
 }
 // Function to update fees for a student by roll number
 void updateFees(int rollNo, float fees) {
 Student* s = findStudentByRollNo(rollNo);
 if (s == NULL)
 {
 throw InvalidFeeException();
 }
 s->fees = fees;
 }
};
int main() {
 // Create an empty array of students
 Student** students = new Student*[100];
 int numStudents = 0;
 // Display menu and get user input
 int choice;
 do {
 // Print top border
 cout << setfill('=') << setw(80) << "" << endl;
 cout << setw(30) << "MENU" << endl;
 cout << setw(80) << setfill('-') << "" << endl;
 cout << setfill(' ');
 cout << "1. Add regular student" << endl;
 cout << "2. Add scholarship student" << endl;
 cout << "3. Display all students" << endl;
 cout << "4. Calculate total fees" << endl;
 cout << "5. Update fees for a student" << endl;
 cout << "6. Delete a student" << endl;
 cout << "0. Exit" << endl;
 // Print bottom border
 cout << setfill('=') << setw(80) << "" << endl;
 cout << "Enter your choice: ";
 cin >> choice;
 switch (choice) {
 case 1: {
 // Get details for a regular student and add to array
 string name;
 int rollNo;
 int standard;
 float fees;
 float discount;
cout << "Enter name: ";
 cin >> name;
 cout << "Enter roll no.: ";
 cin >> rollNo;
 cout << "Enter standard: ";
 cin >> standard;
cout << "Enter fees: ";
 cin >> fees;
 cout << "Enter discount percentage: ";
 cin >> discount;
 students[numStudents] = new RegularStudent(name,
rollNo, standard, fees, discount);
 numStudents++;
 break;
 }
 case 2: {
 // Get details for a scholarship student and add to array
 string name;
 int rollNo;
 int standard;
 float fees;
 float scholarshipAmount;
 cout << "Enter name: ";
 cin >> name;
cout << "Enter roll no.: ";
 cin >> rollNo;
 cout << "Enter standard: ";
 cin >> standard;
 cout << "Enter fees: ";
 cin >> fees;
cout << "Enter scholarship amount: ";
 cin >> scholarshipAmount;
 students[numStudents] = new ScholarshipStudent(name,
rollNo, standard, fees, scholarshipAmount);
 numStudents++;
break;
 }
 case 3:
 {
 // Display all students and their fees
 SchoolFeeCollection school(students, numStudents);
 cout << setw(80) << setfill('=') << "" << endl;
 school.displayAllStudents();
 cout << setw(80) << setfill('=') << "" << endl;
 break;
 }
 case 4: {
 // Calculate total fees for all students
 SchoolFeeCollection school(students, numStudents);
 cout << "Total fees collected: " <<
school.calculateTotalFees() << endl;
 break;
 }
 case 5: {
 // Update fees for a student
int rollNo;
 float newFees;
 cout << "Enter roll no. of student to update fees for: ";
 cin >> rollNo;
 cout << "Enter new fees: ";
 cin >> newFees;
 SchoolFeeCollection school(students, numStudents);
 try {
 school.updateFees(rollNo, newFees);
 cout << "Fees updated successfully!" << endl;
 } catch (InvalidFeeException& e) {
 cout << "Error: " << e.what() << endl;
 }
 break;
 }
 case 6: {
 // Delete a student
 int rollNo;
 cout << "Enter roll no. of student to delete: ";
 cin >> rollNo;
 bool found = false;
 for (int i = 0; i < numStudents; i++) {
 if (students[i]->getRollNo() == rollNo) {
 found = true;
// Delete the student object from memory
delete students[i];
// Shift remaining students to fill the gap
for (int j = i; j < numStudents - 1; j++) {
 students[j] = students[j + 1];
 }
numStudents--;
break;
 }
 }
 if (found) {
 cout << "Student with roll no. " << rollNo << "deleted successfully!"<< endl;
 }
 else
 {
 cout << "Error: Student with roll no. " << rollNo <<
" not found." << endl;
 }
 break;
 }
 case 0:
 // Exit the program
 cout << "Goodbye!" << endl;
 break;
 default:
 // Invalid choice
 cout << "Invalid choice. Please try again." << endl;
 break;
 }
} while (choice != 0);
// Free memory allocated for students
for (int i = 0; i < numStudents; i++) {
 delete students[i];
}
delete[] students;
return 0;
}
