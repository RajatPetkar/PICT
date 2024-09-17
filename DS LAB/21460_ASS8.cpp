#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Set {
private:
    Node* head;

public:
    Set() {
        head = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node{value, nullptr};
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool contains(int value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value)
                return true;
            temp = temp->next;
        }
        return false;
    }

    Set intersection(const Set& otherSet) const {
        Set result;
        Node* temp = head;
        while (temp) {
            if (otherSet.contains(temp->data))
                result.insert(temp->data);
            temp = temp->next;
        }
        return result;
    }

    Set unionSet(const Set& otherSet) const { 
        Set result;
        Node* temp = head;
        while (temp) {
            result.insert(temp->data);
            temp = temp->next;
        }
        temp = otherSet.head;
        while (temp) {
            if (!contains(temp->data))
                result.insert(temp->data);
            temp = temp->next;
        }
        return result;
    }

    Set difference(const Set& otherSet) const { 
        Set result;
        Node* temp = head;
        while (temp) {
            if (!otherSet.contains(temp->data))
                result.insert(temp->data);
            temp = temp->next;
        }
        return result;
    }

    int size() const {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    Set van, bScotch;

    van.insert(1);
    van.insert(2);
    van.insert(3);
    van.insert(5);

    bScotch.insert(2);
    bScotch.insert(3);
    bScotch.insert(4);
    bScotch.insert(6);

    cout << "Students who like both van and bScotch: ";
    Set both = van.intersection(bScotch);
    both.display();

    cout << "Students who like either van or bScotch, but not both: ";
    Set either = van.difference(bScotch).unionSet(bScotch.difference(van));
    either.display();

    cout << "Number of students who like neither van nor bScotch: ";
    int totalStudents = 6;
    Set unionSet = van.unionSet(bScotch);
    int neitherCount = totalStudents - unionSet.size();
    cout << neitherCount << endl;

    return 0;
}
