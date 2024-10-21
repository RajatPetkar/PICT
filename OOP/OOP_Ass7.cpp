#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class PersonInfo
{
    string name, dob, mobileno;

public:
    PersonInfo()
    {
        this->name = "";
        this->dob = "";
        this->mobileno = "";
    }

    PersonInfo(string n, string d, string m)
    {
        this->name = n;
        this->dob = d;
        this->mobileno = m;
    }

    void create()
    {
        cout << "Enter person's details.." << endl;
        cout << "Name of the person: ";
        cin >> this->name;
        cout << "DOB of the person: ";
        cin >> this->dob;
        cout << "MobileNo of the person: ";
        cin >> this->mobileno;
        cout << endl;
    }

    friend bool operator==(const PersonInfo &p1, const PersonInfo &p2)
    {
        return p1.name == p2.name;
    }

    void display()
    {
        cout << "Name: " << this->name << "\tDOB: " << this->dob << "\tMobileNo: " << this->mobileno << endl;
    }

    string getname()
    {
        return this->name;
    }

    string getdob()
    {
        return this->dob;
    }
};

bool comparenames(PersonInfo &p1, PersonInfo &p2)
{
    return p1.getname() < p2.getname();
}

bool comparedob(PersonInfo &p1, PersonInfo &p2)
{
    return p1.getdob() < p2.getdob();
}

int search(vector<PersonInfo> &data, string n)
{
    std::vector<PersonInfo>::iterator i;
    i = std::find(data.begin(), data.end(), PersonInfo(n, "", ""));
    if (i != data.end())
    {
        return int(i - data.begin());
    }
    return -1;
}

int main()
{
    vector<PersonInfo> records;
    char exit;
    exit = 'y';
    int entries = 0,choice;
    cout << "The menu:\n1. Insert\n2. Display\n3. Sort Alphabetically\4. Sort DOB\n5. Search FOR\n6. EXIT\n";
    do
    {
        PersonInfo p;
        string n;
        int index;
        cout << "Enter The choice:";
        cin >> choice;
        cout<<endl;
        switch (choice)
        {
        case 1:
            p.create();
            records.push_back(p);
            entries++;
            cout << endl;
            break;
        case 2:
            cout << "Here are entered details..." << endl;
            for (int i = 0; i < entries; i++)
            {
                records[i].display();
            }
            cout << endl;
            break;
        case 3:
            cout << "Here's the alphabetically sorted list.." << endl;
            sort(records.begin(), records.end(), comparenames);
            for (int i = 0; i < entries; i++)
            {
                records[i].display();
            }
            cout << endl;
            break;
        case 4:
            cout << "Here's the DOB-wise sorted list.." << endl;
            sort(records.begin(), records.end(), comparedob);
            for (int i = 0; i < entries; i++)
            {
                records[i].display();
            }
            cout << endl;
            break;
        case 5:
            cout << "Enter person's name to be found: ";
            cin >> n;
            index = search(records, n);
            if (index == -1)
            {
                cout << "Person not found in the list..." << endl;
            }
            else
            {
                cout << "Here are the person's details.." << endl;
                records[index].display();
            }
            cout << endl;
            break;
        case 6:
            exit = 'n';
            cout << endl;
            break;
        }
    } while (exit == 'y');
    return 0;
}
