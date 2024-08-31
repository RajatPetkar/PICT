#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    string name;
    int roll_number;
    string Class;
    char division;
    string date_of_birth;
    string blood_group;
    string contact_address;
    long long telephone_number;
    string driving_license_no;

    static int student_count;

public:
    Student() {
        name = "";
        roll_number = 0;
        Class = "";
        division = 'A';
        date_of_birth = "";
        blood_group = "";
        contact_address = "";
        telephone_number = 0;
        driving_license_no = "";
        student_count++;
    }

    Student(string name, int roll_number, string Class, char division, string dob, string blood_group, string address, long long phone, string dlno) {
        this->name = name;
        this->roll_number = roll_number;
        this->Class = Class;
        this->division = division;
        date_of_birth = dob;
        this->blood_group = blood_group;
        contact_address = address;
        telephone_number = phone;
        driving_license_no = dlno;
        student_count++;
    }

    Student(const Student &obj) {
        name = obj.name;
        roll_number = obj.roll_number;
        Class = obj.Class;
        division = obj.division;
        date_of_birth = obj.date_of_birth;
        blood_group = obj.blood_group;
        contact_address = obj.contact_address;
        telephone_number = obj.telephone_number;
        driving_license_no = obj.driving_license_no;
        student_count++;
    }

    ~Student() {
        cout << "Destructor called for " << name << endl;
        student_count--;
    }

    static int getStudentCount() {
        return student_count;
    }

    friend void displayStudentData(const Student &student);

    inline void displayName() {
        cout << "Name: " << name << endl;
    }

    void* operator new(size_t size) {
        cout << "Overloading new operator with size: " << size << endl;
        void *p = ::operator new(size);
        return p;
    }

    void operator delete(void *p) {
        cout << "Overloading delete operator" << endl;
        ::operator delete(p);
    }
};

int Student::student_count = 0;

void displayStudentData(const Student &student) {
    cout << "\nStudent Information:" << endl;
    cout << "Name: " << student.name << endl;
    cout << "Roll Number: " << student.roll_number << endl;
    cout << "Class: " << student.Class << endl;
    cout << "Division: " << student.division << endl;
    cout << "Date of Birth: " << student.date_of_birth << endl;
    cout << "Blood Group: " << student.blood_group << endl;
    cout << "Contact Address: " << student.contact_address << endl;
    cout << "Telephone Number: " << student.telephone_number << endl;
    cout << "Driving License No.: " << student.driving_license_no << endl;
}

int main() {
    Student *student1 = new Student("Rajat", 1, "12th", 'A', "01-01-2000", "O+", "123 Main St", 9876543210, "DL123456");

    displayStudentData(*student1);

    cout << "Total Students: " << Student::getStudentCount() << endl;

    Student student2 = *student1;
    displayStudentData(student2);

    delete student1;
    cout << "Total Students after deletion: " << Student::getStudentCount() << endl;

    return 0;
}
