#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int TABLE_SIZE = 10;

struct Client{
    string name;
    string phoneNumber;
    bool isReplaced;
};

class HashTable {
private:
    vector<Client> table;
   
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE, {"", "", false}) {};

    void insert(const string &name,const string& phone){
        int index = hashFunction(name);
        while(table[index].name!= "" && table[index].name!=name){
            index = (index+1)%TABLE_SIZE;
        }
        table[index] = {name,phone,false};
    }

    // void insertWith(const string &name,const string& phone){
    //     int index = hashFunction(name);
    //     if (table[index].name == "" || table[index].isReplaced) {
    //         table[index] = {name, phone, false};
    //     }else{
    //         if (hashFunction(table[index].name) != index) { 
    //             Client replacedClient = table[index];
    //             table[index] = {name, phone, false};
    //             insertWith(replacedClient.name, replacedClient.phoneNumber);
    //         } else {
               
    //             while (table[index].name != "" && table[index].name != name) {
    //                 index = (index + 1) % TABLE_SIZE;
    //             }
    //             table[index] = {name, phone, false};
    //         }
    //     }
    // }

    pair<string, int> search(const string& name) {
        int index = hashFunction(name);
        int comparisons = 1;
        while (table[index].name != "" && table[index].name != name) {
            index = (index + 1) % TABLE_SIZE;
            comparisons++;
        }
        if (table[index].name == name) {
            return {table[index].phoneNumber, comparisons};
        }
        return {"Not found", comparisons};
    }

   
    void display() {
        cout << endl;
        cout<<"Index\tName\tPhone\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].name != "") {
                cout << i <<"\t"<< table[i].name <<"\t" << table[i].phoneNumber;
                cout << endl;
            }else{
                cout << i  << "\t--" << "\t--";
                cout << endl;
            }
        }
    }
};

int main() {
    HashTable ht;

    int cli,choice;
    string name,phone,search;
    
    while(true){

    
    cout<<"\n1.Insert without Replacement\n2.Search\n3.Display\n4.Exit\n\n";
    cin>>choice;

   
        if(choice == 1){
            cout<<"How many entries you want to enter ??";
            cin>>cli;

            for(int i=0;i<cli;i++){
                cout<<"Enter name and phone of "<<i+1<<"client :- ";
                cin>>name;
                cin>>phone;
                ht.insert(name,phone);
            }   
        }
            
           
        if(choice == 2){
            cout<<"Enter name to search :- ";
            cin>>search;
            vector<string> searchNames = {};
            searchNames.push_back(search);

            cout <<endl<<"Search Results (Without Replacement):" << endl;
            int total= 0;
        
            for (const string& name : searchNames) {
                auto result = ht.search(name);
                cout << name << ": " << result.first << " (Comparisons: " << result.second << ")" << endl;
                total += result.second;
            }

            cout << "\nTotal Comparisons (Without Replacement): " << total << endl;

        }
        if(choice == 3){
            ht.display();
        }
        if(choice == 4){
            exit(1);
        }
    }
   

    return 0;
}
