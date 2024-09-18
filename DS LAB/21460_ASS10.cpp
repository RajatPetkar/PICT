#include <iostream>
#include <string>

using namespace std;

class Stack {
private:
    int top;
    int maxSize;
    char* arr; 

public:
    Stack(int size) {
        maxSize = size;
        arr = new char[maxSize];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(char value) {
        if (top == maxSize - 1) {
            cout << "Stack Overflow" << endl;
            return;
        }
        arr[++top] = value;
    }

    char pop() {
        if (top == -1) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return arr[top--];
    }

    char peek() {
        if (top == -1) {
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char ch) {
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}

string infixToPostfix(const string& infix) {
    Stack s(infix.length());
    string postfix;

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        }
        else if (isOperator(ch)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

int evaluatePostfix(const string& postfix) {
    Stack s(postfix.length());
    
    for (char ch : postfix) {
        if (isalnum(ch)) {
            s.push(ch - '0');  
        }
        else if (isOperator(ch)) {
            int operand2 = s.pop();  
            int operand1 = s.pop(); 
            
            int result;
            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }
            s.push(result); 
        }
    }

    return s.pop(); 
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Evaluation Result: " << result << endl;

    return 0;
}
