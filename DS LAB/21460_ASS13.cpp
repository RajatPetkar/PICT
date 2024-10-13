#include <iostream>
using namespace std;

#define MAX 5 

class Deque {
private:
    int arr[MAX];    
    int front;       
    int rear;       
    int size;        

public:
    Deque() {
        front = -1;
        rear = -1;
        size = 0;
    }

    bool isFull() {
        return (size == MAX);
    }

    bool isEmpty() {
        return (size == 0);
    }

    void insertFront(int item) {
        if (isFull()) {
            cout << "Deque is full. Cannot insert at front." << endl;
            return;
        }

        front = (front - 1 + MAX) % MAX;
        arr[front] = item;
        size++;

        if (rear == -1) rear = front;

        cout << "Inserted " << item << " at the front." << endl;
    }

    void insertRear(int item) {
        if (isFull()) {
            cout << "Deque is full. Cannot insert at rear." << endl;
            return;
        }

        rear = (rear + 1) % MAX;
        arr[rear] = item;
        size++;

        if (front == -1) front = rear;

        cout << "Inserted " << item << " at the rear." << endl;
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from front." << endl;
            return;
        }

        cout << "Deleted " << arr[front] << " from the front." << endl;

        front = (front + 1) % MAX;
        size--;

        if (size == 0) {
            front = -1;
            rear = -1;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from rear." << endl;
            return;
        }

        cout << "Deleted " << arr[rear] << " from the rear." << endl;

        rear = (rear - 1 + MAX) % MAX;
        size--;

        if (size == 0) {
            front = -1;
            rear = -1;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is empty!" << endl;
            return;
        }

        cout << "Current Deque: ";
        int i = front;
        for (int count = 0; count < size; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    Deque dq;

    int choice, item;

    do {
        cout << "\nDeque Menu:" << endl;
        cout << "1. Insert at Front" << endl;
        cout << "2. Insert at Rear" << endl;
        cout << "3. Delete from Front" << endl;
        cout << "4. Delete from Rear" << endl;
        cout << "5. Display Deque" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the item to insert at front: ";
            cin >> item;
            dq.insertFront(item);
            break;

        case 2:
            cout << "Enter the item to insert at rear: ";
            cin >> item;
            dq.insertRear(item);
            break;

        case 3:
            dq.deleteFront();
            break;

        case 4:
            dq.deleteRear();
            break;

        case 5:
            dq.display();
            break;

        case 6:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "AANDHA HAI KYA !!" << endl;
        }
    } while (choice != 6);

    return 0;
}
