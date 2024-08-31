// Prblm Stmt: Develop an object oriented program in C++ to create a database of student information
// system containing the following information: Name, Roll number, Class, division, Date of
// Birth, Blood group, Contact address, telephone number, driving license no. and other.
// Construct the database with suitable member functions for initializing and destroying the
// data viz constructor, default constructor, Copy constructor, destructor, static member
// functions, friend class, this pointer, inline code and dynamic memory allocation
// operators-new and delete

#include<iostream>
using namespace std;

// Class to get student generic data
class Student
{
private:
    /* data */
public:
    // constructor  
    Student()
    {
       string name;
       int mob;
       int roll_no;
       string classname;
    };
    int getdata(void)
    {
    int n1, n2;
    string n3;
    cout << "Enter Properties: ";
    cout << "Roll number: ";
    cin >> n1;
    cout << "Contact number: ";
    cin >> n2;
    cout << "NAME: ";
    cin >> n3;
    return n1,n2,n3;
    }
    
    void display(int n1, int n2, string n3)
    {
    cout << n1 << " " << n2 << " " << n3 << endl;
    return;
    };

};
// class that stores personal data of the students
class Personal
{
private:
    Personal(string dob, string bloodgrp, string address, string DLnumber){
        dob = " ";
        bloodgrp=" ";
        address=" ";
        DLnumber=" ";
    }
public:

    friend class Student;
};

int main()

{
    Student s;
    s.getdata();
    return 0;
}