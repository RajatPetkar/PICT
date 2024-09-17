#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void append(Node*& head, int data) {
    Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void display(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        temp = temp->next;
    }
    cout << endl;
}

void onesComplement(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        temp->data = (temp->data == 0) ? 1 : 0;
        temp = temp->next;
    }
}

void twosComplement(Node* head) {
    onesComplement(head);

    Node* temp = head;
    Node* last = nullptr;

    while (temp->next != nullptr) {
        temp = temp->next;
    }
    last = temp;

    int carry = 1;
    while (last != nullptr && carry) {
        int sum = last->data + carry;
        last->data = sum % 2;
        carry = sum / 2;
        last = last->prev;
    }
}

Node* addBinaryNumbers(Node* head1, Node* head2) {
    Node* result = nullptr;
    Node* temp1 = head1;
    Node* temp2 = head2;

    while (temp1->next != nullptr) {
        temp1 = temp1->next;
    }
    while (temp2->next != nullptr) {
        temp2 = temp2->next;
    }

    int carry = 0;
    while (temp1 != nullptr || temp2 != nullptr || carry != 0) {
        int sum = carry;

        if (temp1 != nullptr) {
            sum += temp1->data;
            temp1 = temp1->prev;
        }
        if (temp2 != nullptr) {
            sum += temp2->data;
            temp2 = temp2->prev;
        }

        append(result, sum % 2);
        carry = sum / 2;
    }

    Node* prev = nullptr;
    Node* current = result;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    result = prev;

    return result;
}

int main() {
    Node* bin1 = nullptr;
    Node* bin2 = nullptr;

    append(bin1, 1); 
    append(bin1, 1);
    append(bin1, 0);
    append(bin1, 1);

    append(bin2, 1); 
    append(bin2, 0);
    append(bin2, 1);
    append(bin2, 1);

    cout << "First Binary Number: ";
    display(bin1);

    cout << "Second Binary Number: ";
    display(bin2);

    onesComplement(bin1);
    cout << "1's Complement of First Binary Number: ";
    display(bin1);

    twosComplement(bin1);
    cout << "2's Complement of First Binary Number: ";
    display(bin1);

    Node* sum = addBinaryNumbers(bin1, bin2);
    cout << "Sum of Binary Numbers: ";
    display(sum);

    return 0;
}
