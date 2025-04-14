#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    string division;
    string address;
};

void addStudent() {
    Student s;
    ofstream out("students.txt", ios::app);
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Division: ";
    cin >> s.division;
    cout << "Enter Address: ";
    cin >> s.address;
    out << s.roll << " " << s.name << " " << s.division << " " << s.address << endl;
    out.close();
}

void displayStudent(int roll) {
    ifstream in("students.txt");
    Student s;
    bool found = false;
    while (in >> s.roll >> s.name >> s.division >> s.address) {
        if (s.roll == roll) {
            cout << "Roll: " << s.roll << "\nName: " << s.name
                 << "\nDivision: " << s.division << "\nAddress: " << s.address << endl;
            found = true;
            break;
        }
    }
    in.close();
    if (!found)
        cout << "Student record not found." << endl;
}

void deleteStudent(int roll) {
    ifstream in("students.txt");
    ofstream out("temp.txt");
    Student s;
    bool found = false;

    while (in >> s.roll >> s.name >> s.division >> s.address) {
        if (s.roll == roll) {
            found = true;
            continue;
        }
        out << s.roll << " " << s.name << " " << s.division << " " << s.address << endl;
    }

    in.close();
    out.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record deleted." << endl;
    else
        cout << "Student record not found." << endl;
}

int main() {
    int choice, roll;
    do {
        cout << "\n1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 3:
                cout << "Enter Roll Number to display: ";
                cin >> roll;
                displayStudent(roll);
                break;
        }
    } while (choice != 4);

    return 0;
}
