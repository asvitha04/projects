#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


class InvalidFeeException : public exception {
public:
    const char* what() const throw() {
        return "Invalid changes!";
    }
};


class Student {
public:
    string name;
    int rollNo;
    int standard;
    float fees;

    
    Student() {}

    
    Student(string n, int r, int s, float f) : name(n), rollNo(r), standard(s), fees(f) {}

    
    virtual float calculateFees() {
        return fees;
    }

    int getRollNo() {
        return rollNo;
    }

    
    friend class SchoolFeeCollection;

    
    bool operator < (const Student& s) {
        return rollNo < s.rollNo;
    }
};


class RegularStudent : public Student {
protected:
    float discount;
public:
    
    RegularStudent() {}

    
    RegularStudent(string n, int r, int s, float f, float d) : Student(n, r, s, f), discount(d) {}

    
    float calculateFees() override {
        return fees - (fees * discount / 100);
    }
};


class ScholarshipStudent : public Student {
protected:
    float scholarshipAmount;
public:
  
    ScholarshipStudent() {}

    
    ScholarshipStudent(string n, int r, int s, float f, float sa) : Student(n, r, s, f), scholarshipAmount(sa) {}

    
    float calculateFees() override {
        return fees - scholarshipAmount;
    }
};

class SchoolFeeCollection {
public:
    int numStudents;
    Student** students;

    SchoolFeeCollection() {
        numStudents = 0;
        students = new Student*[100]; 
    }

  
    SchoolFeeCollection(Student** s, int n) {
        numStudents = n;
        students = new Student*[numStudents]; 
        for (int i = 0; i < numStudents; i++) {
            students[i] = s[i];
        }
    }

    
    inline void displayStudentDetails(Student* s) {
        cout << "Name: " << s->name << endl;
        cout << "Roll No.: " << s->rollNo << endl;
        cout << "Standard: " << s->standard << endl;
        cout << "Fees: " << s->fees << endl;
    }

    
    void displayAllStudents() {
        for (int i = 0; i < numStudents; i++) {
            cout << "Student " << i+1 << ":" << endl;
            displayStudentDetails(students[i]);
            cout << "Total fees: " << students[i]->calculateFees() << endl;
            cout << setw(80) << setfill('=') << "" << endl;
        }
    }

   
    float calculateTotalFees() {
        float total = 0;
        for (int i = 0; i < numStudents; i++) {
            total += students[i]->calculateFees();
        }
        return total;
    }


    Student* findStudentByRollNo(int rollNo) {
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->rollNo == rollNo) {
                return students[i];
            }
        }
        return NULL;
    }

    void addRegularStudent(string name, int rollNo, int standard, float fees, float discount) {
        RegularStudent* rs = new RegularStudent(name, rollNo, standard, fees, discount);
        students[numStudents++] = rs;
    }

   
    void addScholarshipStudent(string name, int rollNo, int standard, float fees, float scholarshipAmount) {
        ScholarshipStudent* ss = new ScholarshipStudent(name, rollNo, standard, fees, scholarshipAmount);
        students[numStudents++] = ss;
    }

   
    bool deleteStudent(int rollNo) {
    
        int index = -1;
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->rollNo == rollNo) {
                index = i;
                break;
            }
        }
       
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

    
    void updateFees(int rollNo, float fees) {
        Student* s = findStudentByRollNo(rollNo);
        if (s == NULL) {
            throw InvalidFeeException();
        }
        s->fees = fees;
    }
};

int main() {
   
    Student** students = new Student*[100];
    int numStudents = 0;

    
    int choice;
    do {
       
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
        cout << setfill('=') << setw(80) << "" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
           
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
                students[numStudents] = new RegularStudent(name, rollNo, standard, fees, discount);
                numStudents++;
                break;
            }
            case 2: {
               
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
                students[numStudents] = new ScholarshipStudent(name, rollNo, standard, fees, scholarshipAmount);
                numStudents++;
                break;
            }
            case 3: {
              
                SchoolFeeCollection school(students, numStudents);
                school.displayAllStudents();
                break;
            }
            case 4: {
           
                SchoolFeeCollection school(students, numStudents);
                cout << "Total fees collected: " << school.calculateTotalFees() << endl;
                break;
            }
            case 5: {
            
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
             
                int rollNo;
                cout << "Enter roll no. of student to delete: ";
                cin >> rollNo;
                SchoolFeeCollection school(students, numStudents);
                if (school.deleteStudent(rollNo)) {
                    cout << "Student with roll no. " << rollNo << " deleted successfully!" << endl;
                    numStudents--;
                } else {
                    cout << "Error: Student with roll no. " << rollNo << " not found." << endl;
                }
                break;
            }
            case 0:
             
                cout << "Goodbye!" << endl;
                break;
            default:
              
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 0);

    for (int i = 0; i < numStudents; i++) {
        delete students[i];
    }
    delete[] students;
    return 0;
}

