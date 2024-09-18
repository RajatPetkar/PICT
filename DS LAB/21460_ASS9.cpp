#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    struct Node {
        char data;
        Node* next;
    };
    
    Node* top;  
    
public:
    Stack() {
        top = nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            pop(); 
        }
    }

    void push(char value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    char peek() const {
        if (top != nullptr) {
            return top->data;
        }
        return '\0';
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

bool isWellParenthesized(const string& expression) {
    Stack s;  

    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty() || !isMatchingPair(s.peek(), ch)) {
                return false;  
            }
            s.pop();
        }
    }
    return s.isEmpty();
}

int main() {
    string expression;

    cout << "Enter an expression: ";
    getline(cin, expression);

    if (isWellParenthesized(expression)) {
        cout << "The expression is well parenthesized." << endl;
    } else {
        cout << "The expression is not well parenthesized." << endl;
    }

    return 0;
}
