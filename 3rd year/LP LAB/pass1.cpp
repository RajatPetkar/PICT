#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct OptabEntry {
    string mnemonic;
    string classType;
    int opcode;

    OptabEntry() = default; // <-- add this
    OptabEntry(string m, string c, int o) : mnemonic(m), classType(c), opcode(o) {}
};

struct Symbol {
    string symbol;
    int address;
    bool defined;

    Symbol() = default; // <-- add this
    Symbol(string s, int a, bool d) : symbol(s), address(a), defined(d) {}
};

struct Literal {
    string literal;
    int address;

    Literal() = default; // <-- add this
    Literal(string l, int a) : literal(l), address(a) {}
};


map<string, OptabEntry> OPTAB;
map<string, Symbol> SYMTAB;
vector<Literal> LITTAB;
vector<int> POOLTAB;

int IC = 0;
int literalPointer = 0;

void initializeOPTAB() {
    OPTAB["START"] = OptabEntry("START", "AD", 1);
    OPTAB["END"]   = OptabEntry("END",   "AD", 2);
    OPTAB["ORIGIN"]= OptabEntry("ORIGIN","AD", 3);
    OPTAB["EQU"]   = OptabEntry("EQU",   "AD", 4);
    OPTAB["LTORG"] = OptabEntry("LTORG", "AD", 5);

    OPTAB["MOV"]   = OptabEntry("MOV", "IS", 1);
    OPTAB["ADD"]   = OptabEntry("ADD", "IS", 2);
    OPTAB["SUB"]   = OptabEntry("SUB", "IS", 3);
    OPTAB["MUL"]   = OptabEntry("MUL", "IS", 4);
    OPTAB["DIV"]   = OptabEntry("DIV", "IS", 5);

    OPTAB["DC"]    = OptabEntry("DC",  "DL", 1);
    OPTAB["DS"]    = OptabEntry("DS",  "DL", 2);
}

void processLiterals() {
    if (literalPointer == LITTAB.size()) return;
    POOLTAB.push_back(literalPointer);
    while (literalPointer < LITTAB.size()) {
        LITTAB[literalPointer].address = IC++;
        literalPointer++;
    }
}

vector<string> tokenize(const string& line) {
    vector<string> tokens;
    string token;
    istringstream stream(line);
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    initializeOPTAB();
    POOLTAB.push_back(0);

    ifstream infile("input.asm");
    string line;

    while (getline(infile, line)) {
        if (line.empty()) continue;

        // Remove commas
        replace(line.begin(), line.end(), ',', ' ');
        vector<string> tokens = tokenize(line);

        string label = "", opcode = "", operand = "";

        if (tokens.size() == 4) {
            label = tokens[0];
            opcode = tokens[1];
            operand = tokens[2] + "," + tokens[3];
        } else if (tokens.size() == 3) {
            if (OPTAB.find(tokens[0]) != OPTAB.end()) {
                opcode = tokens[0];
                operand = tokens[1] + "," + tokens[2];
            } else {
                label = tokens[0];
                opcode = tokens[1];
                operand = tokens[2];
            }
        } else if (tokens.size() == 2) {
            opcode = tokens[0];
            operand = tokens[1];
        } else if (tokens.size() == 1) {
            opcode = tokens[0];
        } else {
            cout << "Invalid instruction format: " << line << endl;
            continue;
        }

        if (!label.empty()) {
            if (SYMTAB.find(label) == SYMTAB.end()) {
                SYMTAB[label] = Symbol(label, IC, true);
            } else if (!SYMTAB[label].defined) {
                SYMTAB[label].address = IC;
                SYMTAB[label].defined = true;
            } else {
                cout << "Error: Duplicate symbol " << label << endl;
            }
        }

        auto it = OPTAB.find(opcode);
        if (it == OPTAB.end()) {
            cout << "Invalid Opcode: " << opcode << endl;
            continue;
        }

        string classType = it->second.classType;

        if (classType == "AD") {
            if (opcode == "START") {
                IC = stoi(operand);
            } else if (opcode == "END" || opcode == "LTORG") {
                processLiterals();
            } else if (opcode == "ORIGIN") {
                if (SYMTAB.find(operand) != SYMTAB.end()) {
                    IC = SYMTAB[operand].address;
                } else {
                    try {
                        IC = stoi(operand);
                    } catch (...) {
                        cout << "Invalid ORIGIN operand: " << operand << endl;
                    }
                }
            } else if (opcode == "EQU") {
                if (label.empty()) {
                    cout << "EQU without label" << endl;
                } else {
                    int value;
                    try {
                        value = stoi(operand);
                    } catch (...) {
                        if (SYMTAB.find(operand) != SYMTAB.end()) {
                            value = SYMTAB[operand].address;
                        } else {
                            cout << "Invalid EQU operand: " << operand << endl;
                            continue;
                        }
                    }
                    SYMTAB[label] = Symbol(label, value, true);
                }
            }
        } else if (classType == "IS") {
            if (!operand.empty()) {
                istringstream ops(operand);
                string op;
                while (getline(ops, op, ',')) {
                    op = op.substr(op.find_first_not_of(" \t"));
                    if (!op.empty() && op[0] == '=') {
                        auto found = find_if(LITTAB.begin(), LITTAB.end(), [&](Literal& l) {
                            return l.literal == op;
                        });
                        if (found == LITTAB.end()) {
                            LITTAB.push_back(Literal(op, -1));
                        }
                    }
                }
            }
            IC++;
        } else if (classType == "DL") {
            if (opcode == "DC") {
                IC++;
            } else if (opcode == "DS") {
                try {
                    IC += stoi(operand);
                } catch (...) {
                    cout << "Invalid DS operand: " << operand << endl;
                }
            }
        }
    }

    infile.close();

    // Output tables
    cout << "\nInstruction Counter (IC): " << IC << endl;

    cout << "\nSYMTAB:\nSymbol\tAddress" << endl;
    for (auto& [name, sym] : SYMTAB) {
        cout << name << "\t" << sym.address << endl;
    }

    cout << "\nLITTAB:\nLiteral\tAddress" << endl;
    for (const auto& lit : LITTAB) {
        cout << lit.literal << "\t" << lit.address << endl;
    }

    cout << "\nPOOLTAB:\nPoolIndex" << endl;
    for (int idx : POOLTAB) {
        cout << idx << endl;
    }

    return 0;
}
