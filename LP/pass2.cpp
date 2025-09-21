#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

// Symbol and Literal Table
map<string, int> addressTable;

int main() {
    // Load symbol table
    ifstream symFile("symbol.txt");
    string symbol;
    int address;
    while(symFile >> symbol >> address) {
        addressTable[symbol] = address;
    }
    symFile.close();
    
    // Process intermediate code
    ifstream intermediate("intermediate.txt");
    ofstream output("output.txt");
    
    string line;
    
    cout << "PASS 2 OUTPUT:\n";
    cout << "LC\tMachine Code\tLabel\tOpcode\tOperand\n";
    cout << "------------------------------------------------\n";
    
    while(getline(intermediate, line)) {
        istringstream iss(line);
        int LC;
        string label, opcode, operand;
        iss >> LC >> label >> opcode >> operand;
        
        string machineCode = "";
        
        // Handle machine instructions (2-digit opcodes)
        if(opcode.length() == 2 && isdigit(opcode[0])) {
            machineCode = opcode;
            
            // Resolve operand address
            if(operand != "-" && !operand.empty()) {
                if(operand[0] == '=') {
                    // Literal
                    machineCode += " " + to_string(addressTable[operand]);
                } else if(isdigit(operand[0])) {
                    // Constant
                    machineCode += " " + operand;
                } else {
                    // Symbol
                    machineCode += " " + to_string(addressTable[operand]);
                }
            }
        }
        // Handle DC directive
        else if(opcode == "DL02") {
            machineCode = "00 " + operand;
        }
        
        // Write to output file
        if(!machineCode.empty()) {
            output << LC << " " << machineCode << "\n";
        }
        
        cout << LC << "\t" << machineCode << "\t\t" << label 
             << "\t" << opcode << "\t" << operand << "\n";
    }
    
    intermediate.close();
    output.close();
    
    cout << "\nPass 2 completed. Object code saved in output.txt\n";
    
    return 0;
}