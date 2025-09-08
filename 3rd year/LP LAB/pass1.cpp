// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <map>
// #include <vector>
// #include <iomanip>
// #include <algorithm>

// using namespace std;

// struct OptabEntry {
//     string mnemonic;
//     string classType;
//     int opcode;

//     OptabEntry() = default;
//     OptabEntry(string m, string c, int o) : mnemonic(m), classType(c), opcode(o) {}
// };

// struct Symbol {
//     string symbol;
//     int address;
//     bool defined;

//     Symbol() = default;
//     Symbol(string s, int a, bool d) : symbol(s), address(a), defined(d) {}
// };

// struct Literal {
//     string literal;
//     int address;

//     Literal() = default;
//     Literal(string l, int a) : literal(l), address(a) {}
// };

// map<string, OptabEntry> OPTAB;
// map<string, Symbol> SYMTAB;
// vector<Literal> LITTAB;
// vector<int> POOLTAB;

// int IC = 0;
// int literalPointer = 0;

// void initializeOPTAB() {
//     OPTAB["START"] = OptabEntry("START", "AD", 1);
//     OPTAB["END"]   = OptabEntry("END",   "AD", 2);
//     OPTAB["ORIGIN"]= OptabEntry("ORIGIN","AD", 3);
//     OPTAB["EQU"]   = OptabEntry("EQU",   "AD", 4);
//     OPTAB["LTORG"] = OptabEntry("LTORG", "AD", 5);

//     OPTAB["MOV"]   = OptabEntry("MOV", "IS", 1);
//     OPTAB["ADD"]   = OptabEntry("ADD", "IS", 2);
//     OPTAB["SUB"]   = OptabEntry("SUB", "IS", 3);
//     OPTAB["MUL"]   = OptabEntry("MUL", "IS", 4);
//     OPTAB["DIV"]   = OptabEntry("DIV", "IS", 5);

//     OPTAB["DC"]    = OptabEntry("DC",  "DL", 1);
//     OPTAB["DS"]    = OptabEntry("DS",  "DL", 2);
// }

// void processLiterals() {
//     if (literalPointer == LITTAB.size()) return;
//     POOLTAB.push_back(literalPointer);
//     while (literalPointer < LITTAB.size()) {
//         LITTAB[literalPointer].address = IC;
//         cout << setw(4) << setfill('0') << IC << "\t(DL,01)\t(C," << LITTAB[literalPointer].literal.substr(2, LITTAB[literalPointer].literal.size()-3) << ")" << endl;
//         IC++;
//         literalPointer++;
//     }
// }

// vector<string> tokenize(const string& line) {
//     vector<string> tokens;
//     string token;
//     istringstream stream(line);
//     while (stream >> token) {
//         tokens.push_back(token);
//     }
//     return tokens;
// }

// int main() {
//     initializeOPTAB();
//     POOLTAB.push_back(0);

//     ifstream infile("input.asm");
//     string line;

//     cout << "\nIntermediate Code:\nAddress\tCode\n";
//     while (getline(infile, line)) {
//         if (line.empty()) continue;

//         // Remove commas
//         replace(line.begin(), line.end(), ',', ' ');
//         vector<string> tokens = tokenize(line);

//         string label = "", opcode = "", operand = "";

//         if (tokens.size() == 4) {
//             label = tokens[0];
//             opcode = tokens[1];
//             operand = tokens[2] + "," + tokens[3];
//         } else if (tokens.size() == 3) {
//             if (OPTAB.find(tokens[0]) != OPTAB.end()) {
//                 opcode = tokens[0];
//                 operand = tokens[1] + "," + tokens[2];
//             } else {
//                 label = tokens[0];
//                 opcode = tokens[1];
//                 operand = tokens[2];
//             }
//         } else if (tokens.size() == 2) {
//             opcode = tokens[0];
//             operand = tokens[1];
//         } else if (tokens.size() == 1) {
//             opcode = tokens[0];
//         } else {
//             cout << "Invalid instruction format: " << line << endl;
//             continue;
//         }

//         if (!label.empty()) {
//             if (SYMTAB.find(label) == SYMTAB.end()) {
//                 SYMTAB[label] = Symbol(label, IC, true);
//             } else if (!SYMTAB[label].defined) {
//                 SYMTAB[label].address = IC;
//                 SYMTAB[label].defined = true;
//             } else {
//                 cout << "Error: Duplicate symbol " << label << endl;
//             }
//         }

//         auto it = OPTAB.find(opcode);
//         if (it == OPTAB.end()) {
//             cout << "Invalid Opcode: " << opcode << endl;
//             continue;
//         }

//         string classType = it->second.classType;
//         int opcodeVal = it->second.opcode;

//         if (classType == "AD") {
//             if (opcode == "START") {
//                 IC = stoi(operand);
//                 cout << setw(4) << setfill('0') << IC << "\t(AD,01)\t(C," << operand << ")" << endl;
//             } else if (opcode == "END") {
//                 cout << setw(4) << setfill('0') << IC << "\t(AD,02)" << endl;
//                 processLiterals();
//             } else if (opcode == "LTORG") {
//                 cout << setw(4) << setfill('0') << IC << "\t(AD,05)" << endl;
//                 processLiterals();
//             } else if (opcode == "ORIGIN") {
//                 if (SYMTAB.find(operand) != SYMTAB.end()) {
//                     IC = SYMTAB[operand].address;
//                     cout << setw(4) << setfill('0') << IC << "\t(AD,03)\t(S," << operand << ")" << endl;
//                 } else {
//                     try {
//                         IC = stoi(operand);
//                         cout << setw(4) << setfill('0') << IC << "\t(AD,03)\t(C," << operand << ")" << endl;
//                     } catch (...) {
//                         cout << "Invalid ORIGIN operand: " << operand << endl;
//                     }
//                 }
//             } else if (opcode == "EQU") {
//                 if (label.empty()) {
//                     cout << "EQU without label" << endl;
//                 } else {
//                     int value;
//                     try {
//                         value = stoi(operand);
//                         cout << setw(4) << setfill('0') << IC << "\t(AD,04)\t(C," << operand << ")" << endl;
//                     } catch (...) {
//                         if (SYMTAB.find(operand) != SYMTAB.end()) {
//                             value = SYMTAB[operand].address;
//                             cout << setw(4) << setfill('0') << IC << "\t(AD,04)\t(S," << operand << ")" << endl;
//                         } else {
//                             cout << "Invalid EQU operand: " << operand << endl;
//                             continue;
//                         }
//                     }
//                     SYMTAB[label] = Symbol(label, value, true);
//                 }
//             }
//         } else if (classType == "IS") {
//             string intermediate = "";
//             intermediate += "(" + classType + "," + to_string(opcodeVal) + ")";
//             if (!operand.empty()) {
//                 istringstream ops(operand);
//                 string op;
//                 vector<string> operands;
//                 while (getline(ops, op, ',')) {
//                     op = op.substr(op.find_first_not_of(" \t"));
//                     if (!op.empty()) {
//                         if (op[0] == '=') {
//                             auto found = find_if(LITTAB.begin(), LITTAB.end(), [&](Literal& l) {
//                                 return l.literal == op;
//                             });
//                             if (found == LITTAB.end()) {
//                                 LITTAB.push_back(Literal(op, -1));
//                             }
//                             operands.push_back("(L," + to_string(LITTAB.size()-1) + ")");
//                         } else if (SYMTAB.find(op) != SYMTAB.end()) {
//                             operands.push_back("(S," + op + ")");
//                         } else {
//                             operands.push_back("(C," + op + ")");
//                         }
//                     }
//                 }
//                 intermediate += "\t";
//                 for (size_t i = 0; i < operands.size(); ++i) {
//                     intermediate += operands[i];
//                     if (i < operands.size() - 1) intermediate += ",";
//                 }
//             }
//             cout << setw(4) << setfill('0') << IC << "\t" << intermediate << endl;
//             IC++;
//         } else if (classType == "DL") {
//             if (opcode == "DC") {
//                 cout << setw(4) << setfill('0') << IC << "\t(DL,01)\t(C," << operand << ")" << endl;
//                 IC++;
//             } else if (opcode == "DS") {
//                 try {
//                     int size = stoi(operand);
//                     cout << setw(4) << setfill('0') << IC << "\t(DL,02)\t(C," << operand << ")" << endl;
//                     IC += size;
//                 } catch (...) {
//                     cout << "Invalid DS operand: " << operand << endl;
//                 }
//             }
//         }
//     }

//     infile.close();

//     cout << "\nInstruction Counter (IC): " << IC << endl;

//     cout << "\nSYMTAB:\nSymbol\tAddress" << endl;
//     for (auto& s : SYMTAB) {
//         cout << s.first << "\t" << s.second.address << endl;
//     }

//     cout << "\nLITTAB:\nLiteral\tAddress" << endl;
//     for (const auto& lit : LITTAB) {
//         cout << lit.literal << "\t" << lit.address << endl;
//     }

//     cout << "\nPOOLTAB:\nPoolIndex" << endl;
//     for (int idx : POOLTAB) {
//         cout << idx << endl;
//     }

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure for OPTAB entries
struct OptabEntry {
    string mnemonic;
    string classType;
    int opcode;
    int size;

    OptabEntry() : mnemonic(""), classType(""), opcode(0), size(0) {}
    OptabEntry(string m, string c, int o, int s) : mnemonic(m), classType(c), opcode(o), size(s) {}
};

// Structure for SYMTAB entries
struct Symbol {
    string name;
    int address;
    bool defined;

    Symbol() : name(""), address(0), defined(false) {}
    Symbol(string n, int a, bool d) : name(n), address(a), defined(d) {}
};

// Structure for LITTAB entries
struct Literal {
    string value;
    int address;
    bool allocated;

    Literal() : value(""), address(-1), allocated(false) {}
    Literal(string v) : value(v), address(-1), allocated(false) {}
};

// Global tables
map<string, OptabEntry> OPTAB;
map<string, Symbol> SYMTAB;
vector<Literal> LITTAB;
vector<int> POOLTAB;

// Global counters
int LOCCTR = 0;
int START_ADDR = 0;
bool has_start = false;

// Function to initialize the OPTAB
void initializeOPTAB() {
    // Assembler directives
    OPTAB["START"] = OptabEntry("START", "AD", 1, 0);
    OPTAB["END"]   = OptabEntry("END",   "AD", 2, 0);
    OPTAB["ORIGIN"]= OptabEntry("ORIGIN","AD", 3, 0);
    OPTAB["EQU"]   = OptabEntry("EQU",   "AD", 4, 0);
    OPTAB["LTORG"] = OptabEntry("LTORG", "AD", 5, 0);

    // Imperative statements
    OPTAB["MOV"]   = OptabEntry("MOV", "IS", 1, 1);
    OPTAB["ADD"]   = OptabEntry("ADD", "IS", 2, 1);
    OPTAB["SUB"]   = OptabEntry("SUB", "IS", 3, 1);
    OPTAB["MUL"]   = OptabEntry("MUL", "IS", 4, 1);
    OPTAB["DIV"]   = OptabEntry("DIV", "IS", 5, 1);
    OPTAB["JMP"]   = OptabEntry("JMP", "IS", 6, 1);
    OPTAB["JZ"]    = OptabEntry("JZ",  "IS", 7, 1);
    OPTAB["JNZ"]   = OptabEntry("JNZ", "IS", 8, 1);

    // Declarative statements
    OPTAB["DC"]    = OptabEntry("DC",  "DL", 1, 1);
    OPTAB["DS"]    = OptabEntry("DS",  "DL", 2, 0); // Size will be determined by operand
}

// Function to convert string to uppercase
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Function to check if a string is a number
bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Function to process literals
void processLiterals(int startIndex) {
    if (startIndex >= LITTAB.size()) return;
    
    for (int i = startIndex; i < LITTAB.size(); i++) {
        if (!LITTAB[i].allocated) {
            LITTAB[i].address = LOCCTR;
            LITTAB[i].allocated = true;
            LOCCTR += 1; // Assuming each literal takes 1 word
        }
    }
}

// Function to tokenize a line
vector<string> tokenize(const string& line) {
    vector<string> tokens;
    string token;
    istringstream stream(line);
    
    while (stream >> token) {
        // Remove commas from tokens
        token.erase(remove(token.begin(), token.end(), ','), token.end());
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

// Pass 1 of the assembler
void pass1(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool end_seen = false;
    int literalPoolStart = 0;

    cout << "PASS 1:\n";
    cout << "Location\tLabel\tOpcode\tOperand\n";
    cout << "----------------------------------------\n";

    while (getline(infile, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Remove comments (anything after ';')
        size_t commentPos = line.find(';');
        if (commentPos != string::npos) {
            line = line.substr(0, commentPos);
        }
        
        // Tokenize the line
        vector<string> tokens = tokenize(line);
        if (tokens.empty()) continue;
        
        string label = "", opcode = "", operand = "";
        int tokenIndex = 0;
        
        // Check if first token is a label
        if (OPTAB.find(toUpper(tokens[0])) == OPTAB.end() && tokens[0] != "=") {
            label = tokens[0];
            tokenIndex++;
        }
        
        // Get opcode
        if (tokenIndex < tokens.size()) {
            opcode = toUpper(tokens[tokenIndex]);
            tokenIndex++;
        }
        
        // Get operand
        if (tokenIndex < tokens.size()) {
            operand = tokens[tokenIndex];
            tokenIndex++;
        }
        
        // Handle START directive
        if (opcode == "START") {
            if (!operand.empty() && isNumber(operand)) {
                LOCCTR = stoi(operand);
                START_ADDR = LOCCTR;
            }
            has_start = true;
            cout << setw(4) << setfill('0') << LOCCTR << "\t\t" << opcode << "\t" << operand << endl;
            continue;
        }
        
        // If no START, start from 0
        if (!has_start) {
            LOCCTR = 0;
            START_ADDR = 0;
            has_start = true;
        }
        
        // Handle END directive
        if (opcode == "END") {
            cout << "\t\t" << opcode << endl;
            // Process remaining literals
            processLiterals(literalPoolStart);
            end_seen = true;
            break;
        }
        
        // Handle LTORG directive
        if (opcode == "LTORG") {
            cout << "\t\t" << opcode << endl;
            processLiterals(literalPoolStart);
            literalPoolStart = LITTAB.size();
            continue;
        }
        
        // If there's a label, add it to SYMTAB
        if (!label.empty()) {
            if (SYMTAB.find(label) == SYMTAB.end()) {
                SYMTAB[label] = Symbol(label, LOCCTR, true);
            } else {
                if (!SYMTAB[label].defined) {
                    SYMTAB[label].address = LOCCTR;
                    SYMTAB[label].defined = true;
                } else {
                    cerr << "Error: Duplicate symbol '" << label << "'" << endl;
                }
            }
        }
        
        // Check for literals in operand
        if (!operand.empty() && operand[0] == '=') {
            // Check if this literal already exists
            bool found = false;
            for (const auto& lit : LITTAB) {
                if (lit.value == operand) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                LITTAB.push_back(Literal(operand));
            }
        }
        
        // Process the instruction
        auto optabIt = OPTAB.find(opcode);
        if (optabIt != OPTAB.end()) {
            OptabEntry entry = optabIt->second;
            
            if (entry.classType == "IS") {
                cout << setw(4) << setfill('0') << LOCCTR << "\t" 
                     << (label.empty() ? "" : label) << "\t" 
                     << opcode << "\t" << operand << endl;
                LOCCTR += entry.size;
            } 
            else if (entry.classType == "DL") {
                if (opcode == "DC") {
                    cout << setw(4) << setfill('0') << LOCCTR << "\t" 
                         << (label.empty() ? "" : label) << "\t" 
                         << opcode << "\t" << operand << endl;
                    LOCCTR += entry.size;
                } 
                else if (opcode == "DS") {
                    int size = 1;
                    if (!operand.empty() && isNumber(operand)) {
                        size = stoi(operand);
                    }
                    cout << setw(4) << setfill('0') << LOCCTR << "\t" 
                         << (label.empty() ? "" : label) << "\t" 
                         << opcode << "\t" << operand << endl;
                    LOCCTR += size;
                }
            } 
            else if (entry.classType == "AD") {
                cout << setw(4) << setfill('0') << LOCCTR << "\t" 
                     << (label.empty() ? "" : label) << "\t" 
                     << opcode << "\t" << operand << endl;
                
                if (opcode == "ORIGIN") {
                    // Handle ORIGIN directive
                    size_t plusPos = operand.find('+');
                    size_t minusPos = operand.find('-');
                    
                    if (plusPos != string::npos) {
                        string symbol = operand.substr(0, plusPos);
                        string offsetStr = operand.substr(plusPos + 1);
                        if (SYMTAB.find(symbol) != SYMTAB.end() && isNumber(offsetStr)) {
                            LOCCTR = SYMTAB[symbol].address + stoi(offsetStr);
                        }
                    } 
                    else if (minusPos != string::npos) {
                        string symbol = operand.substr(0, minusPos);
                        string offsetStr = operand.substr(minusPos + 1);
                        if (SYMTAB.find(symbol) != SYMTAB.end() && isNumber(offsetStr)) {
                            LOCCTR = SYMTAB[symbol].address - stoi(offsetStr);
                        }
                    } 
                    else {
                        if (SYMTAB.find(operand) != SYMTAB.end()) {
                            LOCCTR = SYMTAB[operand].address;
                        } 
                        else if (isNumber(operand)) {
                            LOCCTR = stoi(operand);
                        }
                    }
                } 
                else if (opcode == "EQU") {
                    // EQU is handled in pass1 for address calculation
                    if (!label.empty()) {
                        if (SYMTAB.find(label) == SYMTAB.end()) {
                            SYMTAB[label] = Symbol(label, 0, false);
                        }
                        
                        size_t plusPos = operand.find('+');
                        size_t minusPos = operand.find('-');
                        
                        if (plusPos != string::npos) {
                            string symbol = operand.substr(0, plusPos);
                            string offsetStr = operand.substr(plusPos + 1);
                            if (SYMTAB.find(symbol) != SYMTAB.end() && isNumber(offsetStr)) {
                                SYMTAB[label].address = SYMTAB[symbol].address + stoi(offsetStr);
                                SYMTAB[label].defined = true;
                            }
                        } 
                        else if (minusPos != string::npos) {
                            string symbol = operand.substr(0, minusPos);
                            string offsetStr = operand.substr(minusPos + 1);
                            if (SYMTAB.find(symbol) != SYMTAB.end() && isNumber(offsetStr)) {
                                SYMTAB[label].address = SYMTAB[symbol].address - stoi(offsetStr);
                                SYMTAB[label].defined = true;
                            }
                        } 
                        else {
                            if (SYMTAB.find(operand) != SYMTAB.end()) {
                                SYMTAB[label].address = SYMTAB[operand].address;
                                SYMTAB[label].defined = true;
                            } 
                            else if (isNumber(operand)) {
                                SYMTAB[label].address = stoi(operand);
                                SYMTAB[label].defined = true;
                            }
                        }
                    }
                }
            }
        } 
        else {
            cerr << "Error: Invalid opcode '" << opcode << "'" << endl;
        }
    }
    
    // If END was not encountered, process remaining literals
    if (!end_seen) {
        processLiterals(literalPoolStart);
    }
    
    infile.close();
    
    cout << "\nPASS 1 COMPLETED\n";
    cout << "Program length: " << (LOCCTR - START_ADDR) << endl;
}

// Pass 2 of the assembler
void pass2(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    int currentLocation = START_ADDR;
    vector<string> machineCode;
    
    cout << "\nPASS 2:\n";
    cout << "Location\tMachine Code\n";
    cout << "----------------------------\n";

    while (getline(infile, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Remove comments
        size_t commentPos = line.find(';');
        if (commentPos != string::npos) {
            line = line.substr(0, commentPos);
        }
        
        // Tokenize the line
        vector<string> tokens = tokenize(line);
        if (tokens.empty()) continue;
        
        string label = "", opcode = "", operand = "";
        int tokenIndex = 0;
        
        // Check if first token is a label
        if (OPTAB.find(toUpper(tokens[0])) == OPTAB.end() && tokens[0] != "=") {
            tokenIndex++;
        }
        
        // Get opcode
        if (tokenIndex < tokens.size()) {
            opcode = toUpper(tokens[tokenIndex]);
            tokenIndex++;
        }
        
        // Get operand
        if (tokenIndex < tokens.size()) {
            operand = tokens[tokenIndex];
            tokenIndex++;
        }
        
        // Skip START directive
        if (opcode == "START") {
            continue;
        }
        
        // Stop at END directive
        if (opcode == "END") {
            break;
        }
        
        // Skip LTORG directive
        if (opcode == "LTORG") {
            continue;
        }
        
        // Process the instruction
        auto optabIt = OPTAB.find(opcode);
        if (optabIt != OPTAB.end()) {
            OptabEntry entry = optabIt->second;
            
            if (entry.classType == "IS") {
                string code = "(" + to_string(entry.opcode) + ") ";
                
                if (!operand.empty()) {
                    if (operand[0] == '=') { // Literal
                        for (const auto& lit : LITTAB) {
                            if (lit.value == operand) {
                                code += to_string(lit.address);
                                break;
                            }
                        }
                    } 
                    else { // Symbol or constant
                        if (SYMTAB.find(operand) != SYMTAB.end()) {
                            code += to_string(SYMTAB[operand].address);
                        } 
                        else if (isNumber(operand)) {
                            code += operand;
                        } 
                        else {
                            code += "0"; // Undefined symbol
                        }
                    }
                } 
                else {
                    code += "0";
                }
                
                cout << setw(4) << setfill('0') << currentLocation << "\t\t" << code << endl;
                machineCode.push_back(code);
                currentLocation += entry.size;
            } 
            else if (entry.classType == "DL") {
                if (opcode == "DC") {
                    string code = "(01) " + operand;
                    cout << setw(4) << setfill('0') << currentLocation << "\t\t" << code << endl;
                    machineCode.push_back(code);
                    currentLocation += entry.size;
                } 
                else if (opcode == "DS") {
                    int size = 1;
                    if (!operand.empty() && isNumber(operand)) {
                        size = stoi(operand);
                    }
                    for (int i = 0; i < size; i++) {
                        cout << setw(4) << setfill('0') << currentLocation << "\t\t(00) 0" << endl;
                        machineCode.push_back("(00) 0");
                        currentLocation += 1;
                    }
                }
            } 
            else if (entry.classType == "AD") {
                if (opcode == "ORIGIN") {
                    // Handle ORIGIN directive
                    size_t plusPos = operand.find('+');
                    size_t minusPos = operand.find('-');
                    
                    if (plusPos != string::npos) {
                        string symbol = operand.substr(0, plusPos);
                        string offsetStr = operand.substr(plusPos + 1);
                        if (SYMTAB.find(symbol) != SYMTAB.end() && isNumber(offsetStr)) {
                            currentLocation = SYMTAB[symbol].address + stoi(offsetStr);
                        }
                    } 
                    else if (minusPos != string::npos) {
                        string symbol = operand.substr(0, minusPos);
                        string offsetStr = operand.substr(minusPos + 1);
                        if (SYMTAB.find(symbol) != SYMTAB.end() && isNumber(offsetStr)) {
                            currentLocation = SYMTAB[symbol].address - stoi(offsetStr);
                        }
                    } 
                    else {
                        if (SYMTAB.find(operand) != SYMTAB.end()) {
                            currentLocation = SYMTAB[operand].address;
                        } 
                        else if (isNumber(operand)) {
                            currentLocation = stoi(operand);
                        }
                    }
                }
                // EQU is handled in pass1, no machine code generated
            }
        }
    }
    
    infile.close();
    
    cout << "\nPASS 2 COMPLETED\n";
}

// Function to display symbol table
void displaySymbolTable() {
    cout << "\nSYMBOL TABLE:\n";
    cout << "Symbol\tAddress\tDefined\n";
    cout << "-----------------------\n";
    for (const auto& entry : SYMTAB) {
        cout << entry.first << "\t" 
             << setw(4) << setfill('0') << entry.second.address << "\t"
             << (entry.second.defined ? "Yes" : "No") << endl;
    }
}

// Function to display literal table
void displayLiteralTable() {
    cout << "\nLITERAL TABLE:\n";
    cout << "Literal\tAddress\n";
    cout << "----------------\n";
    for (const auto& lit : LITTAB) {
        cout << lit.value << "\t" 
             << setw(4) << setfill('0') << lit.address << endl;
    }
}

int main() {
    string filename = "input.asm";
    
    // Initialize the OPTAB
    initializeOPTAB();
    
    // Execute pass 1
    pass1(filename);
    
    // Display tables after pass 1
    displaySymbolTable();
    displayLiteralTable();
    
    // Execute pass 2
    pass2(filename);
    
    return 0;
}
