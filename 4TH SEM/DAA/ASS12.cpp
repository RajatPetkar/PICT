#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int SIZE = 100; // max roll numbers
const int RECORD_SIZE = sizeof(int) + 20 + sizeof(bool); // roll + name + deleted flag

struct Student {
    int roll;
    char name[20];
    bool deleted;
};

int getPos(int roll) {
    return (roll - 1) * sizeof(Student);
}

void insertRecord() {
    Student s;
    cout << "Enter Roll Number (1-100): ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin >> s.name;
    s.deleted = false;

    fstream file("students.dat", ios::in | ios::out | ios::binary);
    if (!file) file.open("students.dat", ios::out | ios::binary); // create file if not exists
    file.seekp(getPos(s.roll));
    file.write((char*)&s, sizeof(Student));
    file.close();
    cout << "Record inserted." << endl;
}

void deleteRecord() {
    int roll;
    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    fstream file("students.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    Student s;
    file.seekg(getPos(roll));
    file.read((char*)&s, sizeof(Student));

    if (s.deleted || s.roll != roll) {
        cout << "Record not found." << endl;
    } else {
        s.deleted = true;
        file.seekp(getPos(roll));
        file.write((char*)&s, sizeof(Student));
        cout << "Record deleted." << endl;
    }
    file.close();
}

void displayRecord() {
    int roll;
    cout << "Enter Roll Number to display: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    Student s;
    file.seekg(getPos(roll));
    file.read((char*)&s, sizeof(Student));
    file.close();

    if (s.deleted || s.roll != roll) {
        cout << "Record not found." << endl;
    } else {
        cout << "Roll: " << s.roll << "\nName: " << s.name << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Insert Record\n2. Delete Record\n3. Display Record\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: insertRecord(); break;
            case 2: deleteRecord(); break;
            case 3: displayRecord(); break;
        }
    } while (choice != 4);
    return 0;
}
