#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, int> states;
    // int n;
    // cout << "Enter no of states you want to enter: ";
    // cin >> n;
    char choice;
    do
    {
        cout << "Enter states name as single string..Dont give spaces.." << endl;
        string s;
        int population;
        cout << "Enter state name without space: ";
        cin >> s;
        cout << "Enter its population: ";
        cin >> population;
        states[s] = population;
        cout << endl;
        cout<<"ANOTHER STATE?(y/n)\n";
        cin>>choice;
        cout << endl;
    } while (choice == 'y');
    
    do
    {
        try
        {
            string state;
            cout << "Enter states name to find its popuation: ";

            cin >> state;
            int p = states[state];
            if (p == 0)
            {
                throw state;
            }
            else
            {
                cout << "The population of " << state << " is " << p << endl;
            }
        }
        catch (string state)
        {
            cout << "No such state exists...." << endl;
        }
        cout << "Continue?(y/n)";
        cin >> choice;
    }
    while (choice == 'y');
    cout<<"thanks";
    return 0;
}