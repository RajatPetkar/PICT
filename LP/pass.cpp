#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

// Machine Operation Table
map<string, string> MOT = {
    {"LOAD", "01"}, {"STORE", "02"}, {"ADD", "03"}, 
    {"SUB", "04"}, {"JMP", "05"}, {"HALT", "06"}
};

// Pseudo Operation Table  
map<string, string> POT = {
    {"START", "AD01"}, {"END", "AD02"}, 
    {"DS", "DL01"}, {"DC", "DL02"}
};

// Symbol Table
map<string, int> symbolTable;

// Literal Table
map<string, int> literalTable;

int main() {
    ifstream input("input.asm");
    ofstream intermediate("intermediate.txt");
    ofstream symTab("symbol.txt");
    
    string line;
    int LC = 0;
    
    cout << "PASS 1 OUTPUT:\n";
    cout << "LC\tLabel\tOpcode\tOperand\n";
    cout << "------------------------------\n";
    
    while(getline(input, line)) {
        if(line.empty() || line[0] == ';') continue;
        
        istringstream iss(line);
        string token1, token2, token3;
        iss >> token1 >> token2 >> token3;
        
        string label = "", opcode = "", operand = "";
        
        // Check if first token is label (ends with :)
        if(token1.back() == ':') {
            label = token1.substr(0, token1.length()-1);
            symbolTable[label] = LC;
            opcode = token2;
            operand = token3;
        } else {
            opcode = token1;
            operand = token2;
        }
        
        // Handle START
        if(opcode == "START") {
            LC = stoi(operand);
            intermediate << LC << " " << label << " " << POT[opcode] 
                        << " " << operand << "\n";
            cout << LC << "\t" << label << "\t" << opcode << "\t" << operand << "\n";
            continue;
        }
        
        // Handle END
        if(opcode == "END") {
            intermediate << LC << " " << label << " " << POT[opcode] << " -\n";
            cout << LC << "\t" << label << "\t" << opcode << "\t-\n";
            break;
        }
        
        // Handle DS
        if(opcode == "DS") {
            intermediate << LC << " " << label << " " << POT[opcode] 
                        << " " << operand << "\n";
            cout << LC << "\t" << label << "\t" << opcode << "\t" << operand << "\n";
            LC += stoi(operand);
            continue;
        }
        
        // Handle DC
        if(opcode == "DC") {
            intermediate << LC << " " << label << " " << POT[opcode] 
                        << " " << operand << "\n";
            cout << LC << "\t" << label << "\t" << opcode << "\t" << operand << "\n";
            LC++;
            continue;
        }
        
        // Handle Machine Instructions
        if(MOT.find(opcode) != MOT.end()) {
            // Add symbol to table if not exists
            if(!operand.empty() && operand[0] != '=' && !isdigit(operand[0])) {
                if(symbolTable.find(operand) == symbolTable.end()) {
                    symbolTable[operand] = -1; // Forward reference
                }
            }
            
            // Handle literals
            if(operand[0] == '=') {
                literalTable[operand] = -1;
            }
            
            intermediate << LC << " " << label << " " << MOT[opcode] 
                        << " " << operand << "\n";
            cout << LC << "\t" << label << "\t" << opcode << "\t" << operand << "\n";
            LC++;
        }
    }
    
    // Allocate literal addresses
    for(auto& lit : literalTable) {
        lit.second = LC++;
    }
    
    // Save symbol table
    for(auto& sym : symbolTable) {
        symTab << sym.first << " " << sym.second << "\n";
    }
    
    // Save literal table to symbol file
    for(auto& lit : literalTable) {
        symTab << lit.first << " " << lit.second << "\n";
    }
    
    cout << "\nSymbol Table:\n";
    for(auto& sym : symbolTable) {
        cout << sym.first << "\t" << sym.second << "\n";
    }
    
    input.close();
    intermediate.close();
    symTab.close();
    
    cout << "\nPass 1 completed. Files created: intermediate.txt, symbol.txt\n";
    
    return 0;
}