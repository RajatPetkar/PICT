#include <iostream>

using namespace std;

// Function to flip the bits of a binary number (One's Complement)
void onesComplement(char binary[], int size) {
    for (int i = 0; i < size; ++i) {
        binary[i] = (binary[i] == '0') ? '1' : '0';
    }
}

// Function to add 1 to a binary number (Two's Complement)
void twosComplement(char binary[], int size) {
    // Step 1: Flip the bits
    onesComplement(binary, size);

    // Step 2: Add 1 to the flipped bits
    int carry = 1;
    for (int i = size - 1; i >= 0; --i) {
        int bitSum = (binary[i] - '0') + carry;
        binary[i] = (bitSum % 2) + '0';
        carry = bitSum / 2;
    }
}

// Function to perform binary addition
void binaryAddition(const char binary1[], const char binary2[], char result[], int size) {
    int carry = 0;

    for (int i = size - 1; i >= 0; --i) {
        int bitSum = (binary1[i] - '0') + (binary2[i] - '0') + carry;
        result[i] = (bitSum % 2) + '0';
        carry = bitSum / 2;
    }
}

// Function to print a binary number
void printBinary(const char binary[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << binary[i];
    }
    cout << endl;
}

int main() {
    const int MAX_SIZE = 32; // Assuming a maximum binary number size of 32 bits
    char binaryNumber[MAX_SIZE];
    char result[MAX_SIZE];

    cout << "Enter a binary number: ";
    cin >> binaryNumber;

    // Validate the input to ensure it's a valid binary number
    for (int i = 0; binaryNumber[i] != '\0'; ++i) {
        if (binaryNumber[i] != '0' && binaryNumber[i] != '1') {
            cout << "Invalid binary number. Please enter a valid binary number." << endl;
            return 1; // Exit with an error code
        }
    }

    int choice;
    cout << "Menu:" << endl;
    cout << "1. One's Complement" << endl;
    cout << "2. Two's Complement" << endl;
    cout << "3. Binary Addition" << endl;
    cout << "Enter your choice (1, 2, or 3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            onesComplement(binaryNumber, MAX_SIZE);
            cout << "One's complement: ";
            printBinary(binaryNumber, MAX_SIZE);
            break;

        case 2:
            twosComplement(binaryNumber, MAX_SIZE);
            cout << "Two's complement: ";
            printBinary(binaryNumber, MAX_SIZE);
            break;

        case 3:
            char binaryNumber2[MAX_SIZE];
            cout << "Enter another binary number for addition: ";
            cin >> binaryNumber2;

            // Validate the second input to ensure it's a valid binary number
            for (int i = 0; binaryNumber2[i] != '\0'; ++i) {
                if (binaryNumber2[i] != '0' && binaryNumber2[i] != '1') {
                    cout << "Invalid binary number. Please enter a valid binary number." << endl;
                    return 1; // Exit with an error code
                }
            }

            binaryAddition(binaryNumber, binaryNumber2, result, MAX_SIZE);
            cout << "Binary Addition: ";
            printBinary(result, MAX_SIZE);
            break;

        default:
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            break;
    }

    return 0;
}
