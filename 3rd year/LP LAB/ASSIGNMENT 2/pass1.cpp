#include <bits/stdc++.h>
using namespace std;

struct Symbol {
    string name;
    int addr;
};

struct Literal {
    string val;
    int addr;
};

map<string, int> opcode, reg, cond, ad, dl;
vector<Symbol> symtab;
vector<Literal> littab;
vector<int> pooltab;
int lc = 0, litIdx = 0;

void init() {
    opcode["STOP"] = 0; opcode["ADD"] = 1; opcode["SUB"] = 2;
    opcode["MULT"] = 3; opcode["MOVER"] = 4; opcode["MOVEM"] = 5;
    opcode["COMP"] = 6; opcode["BC"] = 7; opcode["DIV"] = 8;
    opcode["READ"] = 9; opcode["PRINT"] = 10;
    
    reg["AREG"] = 1; reg["BREG"] = 2; reg["CREG"] = 3; reg["DREG"] = 4;
    
    cond["LT"] = 1; cond["LE"] = 2; cond["EQ"] = 3;
    cond["GT"] = 4; cond["GE"] = 5; cond["ANY"] = 6;
    
    ad["START"] = 1; ad["END"] = 2; ad["ORIGIN"] = 3;
    ad["EQU"] = 4; ad["LTORG"] = 5;
    
    dl["DC"] = 1; dl["DS"] = 2;
}

int findSym(string s) {
    for(int i = 0; i < symtab.size(); i++)
        if(symtab[i].name == s) return i;
    return -1;
}

void addSym(string s, int a = -1) {
    int idx = findSym(s);
    if(idx == -1) symtab.push_back({s, a});
    else if(a != -1) symtab[idx].addr = a;
}

void processLit(ofstream &out) {
    pooltab.push_back(litIdx);
    for(int i = litIdx; i < littab.size(); i++) {
        littab[i].addr = lc;
        out << lc << " (DL,01) (C," << littab[i].val << ")\n";
        lc++;
    }
    litIdx = littab.size();
}

vector<string> tokenize(string line) {
    vector<string> tokens;
    string tok = "";
    for(char c : line) {
        if(c == ' ' || c == ',') {
            if(tok != "") tokens.push_back(tok);
            tok = "";
        } else tok += c;
    }
    if(tok != "") tokens.push_back(tok);
    return tokens;
}

bool isLabel(string s) {
    return opcode.find(s) == opcode.end() && 
           ad.find(s) == ad.end() && 
           dl.find(s) == dl.end();
}

void pass1() {
    ifstream in("source.txt");
    ofstream out("ic.txt");
    string line;
    
    while(getline(in, line)) {
        if(line.empty()) continue;
        
        vector<string> tok = tokenize(line);
        if(tok.empty()) continue;
        
        int i = 0;
        string label = "";
        
        // Handle label
        if(isLabel(tok[i])) {
            label = tok[i];
            addSym(label, lc);
            i++;
        }
        
        if(i >= tok.size()) continue;
        
        // START
        if(tok[i] == "START") {
            lc = stoi(tok[i+1]);
            out << "-x- (AD,01) (C," << tok[i+1] << ")\n";
            continue;
        }
        
        // END or LTORG
        if(tok[i] == "END" || tok[i] == "LTORG") {
            if(tok[i] == "END") out << "-x- (AD,02)\n";
            processLit(out);
            if(tok[i] == "END") break;
            continue;
        }
        
        // ORIGIN
        if(tok[i] == "ORIGIN") {
            string expr = tok[i+1];
            string sym = "";
            char op = ' ';
            int val = 0;
            
            for(int j = 0; j < expr.size(); j++) {
                if(expr[j] == '+' || expr[j] == '-') {
                    op = expr[j];
                    val = stoi(expr.substr(j+1));
                    break;
                }
                sym += expr[j];
            }
            
            int idx = findSym(sym);
            if(op == '+') lc = symtab[idx].addr + val;
            else if(op == '-') lc = symtab[idx].addr - val;
            
            out << "-x- (AD,03) (S," << (idx+1) << ")" << op << val << "\n";
            continue;
        }
        
        // EQU
        if(tok[i] == "EQU") {
            string expr = tok[i+1];
            string sym = "";
            char op = ' ';
            int val = 0;
            
            for(int j = 0; j < expr.size(); j++) {
                if(expr[j] == '+' || expr[j] == '-') {
                    op = expr[j];
                    val = stoi(expr.substr(j+1));
                    break;
                }
                sym += expr[j];
            }
            
            int lidx = findSym(label);
            int ridx = findSym(sym);
            
            if(op == '+') symtab[lidx].addr = symtab[ridx].addr + val;
            else if(op == '-') symtab[lidx].addr = symtab[ridx].addr - val;
            else symtab[lidx].addr = symtab[ridx].addr;
            
            out << "\n";
            continue;
        }
        
        // DC or DS
        if(dl.find(tok[i]) != dl.end()) {
            string val = tok[i+1];
            if(val[0] == '\'') val = val.substr(1, val.size()-2);
            
            out << lc << " (DL," << setfill('0') << setw(2) << dl[tok[i]] 
                << ") (C," << val << ")\n";
            
            if(tok[i] == "DS") lc += stoi(val);
            else lc++;
            continue;
        }
        
        // Instructions
        if(opcode.find(tok[i]) != opcode.end()) {
            int op = opcode[tok[i]];
            out << lc << " (IS," << setfill('0') << setw(2) << op << ")";
            
            if(tok[i] == "STOP") {
                out << "\n";
            } 
            else if(tok[i] == "READ" || tok[i] == "PRINT") {
                int idx = findSym(tok[i+1]);
                if(idx == -1) {
                    addSym(tok[i+1], -1);
                    idx = symtab.size()-1;
                }
                out << " (S," << (idx+1) << ")\n";
            }
            else {
                int r = (tok[i] == "BC") ? cond[tok[i+1]] : reg[tok[i+1]];
                out << " (" << r << ")";
                
                if(tok[i+2][0] == '=') {
                    string lit = tok[i+2].substr(2, tok[i+2].size()-3);
                    littab.push_back({lit, -1});
                    out << " (L," << littab.size() << ")\n";
                } else {
                    int idx = findSym(tok[i+2]);
                    if(idx == -1) {
                        addSym(tok[i+2], -1);
                        idx = symtab.size()-1;
                    }
                    out << " (S," << (idx+1) << ")\n";
                }
            }
            lc++;
        }
    }
    
    in.close();
    out.close();
}

void writeTables() {
    ofstream f("symtab.txt");
    f << left << setw(7) << "Sr.No" << setw(16) << "Symbol" << "Address\n";
    for(int i = 0; i < symtab.size(); i++)
        f << left << setw(7) << (i+1) << setw(16) << symtab[i].name << symtab[i].addr << "\n";
    f.close();
    
    f.open("littab.txt");
    f << left << setw(7) << "Sr.No" << setw(16) << "Literal" << "Address\n";
    for(int i = 0; i < littab.size(); i++)
        f << left << setw(7) << (i+1) << setw(16) << littab[i].val << littab[i].addr << "\n";
    f.close();
    
    f.open("pooltab.txt");
    f << "Literal No.\n";
    for(int p : pooltab) f << (p+1) << "\n";
    f.close();
}

int main() {
    cout << "Pass1 Processing...\n";
    init();
    pass1();
    writeTables();
    cout << "Pass1 Completed!\n";
    cout << "\nGenerated Files:\n";
    cout << "- ic.txt (Intermediate Code)\n";
    cout << "- symtab.txt (Symbol Table)\n";
    cout << "- littab.txt (Literal Table)\n";
    cout << "- pooltab.txt (Pool Table)\n";
    return 0;
}