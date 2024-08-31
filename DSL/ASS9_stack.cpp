#include <iostream>
#include <cctype>

using namespace std;

// Custom stack implementation
class Stack {
private:
    char* array;
    int capacity;
    int top;

public:
    Stack(int size) {
        capacity = size;
        array = new char[size];
        top = -1;
    }

    ~Stack() {
        delete[] array;
    }

    void push(char value) {
        if (top == capacity - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        array[++top] = value;
    }

    char pop() {
        if (top == -1) {
            cout << "Stack underflow!" << endl;
            return '\0';
        }
        return array[top--];
    }

    char peek() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        return array[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to return precedence of operators
int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;  // Assuming lowest precedence for other characters
}

// Function to convert infix expression to postfix expression
string infixToPostfix(const string& infix) {
    Stack s(infix.size() + 1); // +1 for '\0' character

    string postfix;

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;  // If operand, add to the postfix expression
        } else if (ch == '(') {
            s.push(ch);  // If opening parenthesis, push onto the stack
        } else if (ch == ')') {
            // Pop and append operators from the stack until an opening parenthesis is encountered
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();  // Remove the opening parenthesis from the stack
        } else if (isOperator(ch)) {
            // Pop and append operators from the stack with equal or higher precedence
            while (!s.isEmpty() && getPrecedence(ch) <= getPrecedence(s.peek())) {
                postfix += s.pop();
            }
            s.push(ch);  // Push the current operator onto the stack
        }
    }

    // Pop and append remaining operators from the stack
    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

int main() {
    string infixExpression;

    cout << "Enter an infix expression: ";
    cin>>infixExpression;

    string postfixExpression = infixToPostfix(infixExpression);

    cout << "Postfix expression: " << postfixExpression << endl;

    return 0;
}
