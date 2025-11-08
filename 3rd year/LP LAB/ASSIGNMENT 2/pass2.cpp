#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> symtab;
vector<pair<string, int>> littab;

void loadSymtab() {
    ifstream f("symtab.txt");
    if(!f.is_open()) {
        cout << "Error: Cannot open symtab.txt\n";
        exit(1);
    }
    string line;
    getline(f, line); // Skip header
    
    int idx, addr;
    string name;
    while(f >> idx >> name >> addr) {
        symtab.push_back({name, addr});
    }
    f.close();
    cout << "Symbol Table Loaded (" << symtab.size() << " symbols)\n";
}

void loadLittab() {
    ifstream f("littab.txt");
    if(!f.is_open()) {
        cout << "Error: Cannot open littab.txt\n";
        exit(1);
    }
    string line;
    getline(f, line); // Skip header
    
    int idx, addr;
    string lit;
    while(f >> idx >> lit >> addr) {
        littab.push_back({lit, addr});
    }
    f.close();
    cout << "Literal Table Loaded (" << littab.size() << " literals)\n";
}

bool isNumber(const string& s) {
    if(s.empty()) return false;
    for(char c : s) {
        if(!isdigit(c) && c != '-') return false;
    }
    return true;
}

void pass2() {
    ifstream ic("ic.txt");
    if(!ic.is_open()) {
        cout << "Error: Cannot open ic.txt\n";
        exit(1);
    }
    
    ofstream mc("machine_code.txt");
    string line;
    int lineNo = 0;
    
    while(getline(ic, line)) {
        lineNo++;
        if(line.empty()) continue;
        
        cout << "Processing line " << lineNo << ": " << line << endl;
        
        // Remove all spaces for easier parsing
        string clean = "";
        for(char c : line) {
            if(c != ' ') clean += c;
        }
        
        // Skip lines starting with -x-
        if(clean.find("-x-") == 0) {
            cout << "  -> Skipping directive line\n";
            continue;
        }
        
        // Extract location counter if present
        int pos = 0;
        string lc = "";
        while(pos < clean.size() && isdigit(clean[pos])) {
            lc += clean[pos];
            pos++;
        }
        
        if(pos >= clean.size()) continue;
        
        // Now we should be at '(' 
        if(clean[pos] != '(') {
            cout << "  -> Invalid format, skipping\n";
            continue;
        }
        
        pos++; // Skip '('
        
        // Get type (AD, DL, IS)
        string type = "";
        type += clean[pos++];
        type += clean[pos++];
        
        if(clean[pos] != ',') {
            cout << "  -> Expected comma after type\n";
            continue;
        }
        pos++; // Skip ','
        
        // Get code
        string code = "";
        while(pos < clean.size() && isdigit(clean[pos])) {
            code += clean[pos];
            pos++;
        }
        
        if(code.empty()) {
            cout << "  -> No code found\n";
            continue;
        }
        
        int codeNum = stoi(code);
        
        if(clean[pos] != ')') {
            cout << "  -> Expected closing paren\n";
            continue;
        }
        pos++; // Skip ')'
        
        cout << "  -> Type: " << type << ", Code: " << codeNum << endl;
        
        // Handle different types
        if(type == "AD") {
            cout << "  -> Assembler Directive, skipping\n";
            continue;
        }
        else if(type == "DL") {
            // Expect (C,value)
            if(pos >= clean.size() || clean[pos] != '(') continue;
            pos++; // Skip '('
            
            if(clean[pos] != 'C') continue;
            pos++; // Skip 'C'
            
            if(clean[pos] != ',') continue;
            pos++; // Skip ','
            
            string val = "";
            while(pos < clean.size() && clean[pos] != ')') {
                val += clean[pos];
                pos++;
            }
            
            // Remove quotes if present
            if(val.front() == '\'' && val.back() == '\'') {
                val = val.substr(1, val.size()-2);
            }
            
            if(!isNumber(val)) {
                cout << "  -> Warning: Non-numeric value: " << val << "\n";
                continue;
            }
            
            int value = stoi(val);
            
            if(codeNum == 1) { // DC
                mc << "+00 0 " << setfill('0') << setw(3) << value << "\n";
                cout << "  -> DC: +00 0 " << setfill('0') << setw(3) << value << "\n";
            } else if(codeNum == 2) { // DS
                for(int i = 0; i < value; i++) {
                    mc << "+00 0 000\n";
                }
                cout << "  -> DS: " << value << " words\n";
            }
        }
        else if(type == "IS") {
            int reg = 0, addr = 0;
            
            // Check for register (single digit in parens)
            if(pos < clean.size() && clean[pos] == '(') {
                pos++; // Skip '('
                if(isdigit(clean[pos])) {
                    reg = clean[pos] - '0';
                    pos++; // Skip digit
                    pos++; // Skip ')'
                }
            }
            
            // Check for symbol or literal
            if(pos < clean.size() && clean[pos] == '(') {
                pos++; // Skip '('
                char tableType = clean[pos];
                pos++; // Skip 'S' or 'L'
                pos++; // Skip ','
                
                string idx = "";
                while(pos < clean.size() && isdigit(clean[pos])) {
                    idx += clean[pos];
                    pos++;
                }
                
                if(!idx.empty()) {
                    int index = stoi(idx) - 1; // Convert to 0-based
                    
                    if(tableType == 'S' && index >= 0 && index < symtab.size()) {
                        addr = symtab[index].second;
                    } else if(tableType == 'L' && index >= 0 && index < littab.size()) {
                        addr = littab[index].second;
                    }
                }
            }
            
            mc << "+" << setfill('0') << setw(2) << codeNum << " "
               << reg << " " << setfill('0') << setw(3) << addr << "\n";
            
            cout << "  -> IS: +" << setfill('0') << setw(2) << codeNum 
                 << " " << reg << " " << setfill('0') << setw(3) << addr << "\n";
        }
    }
    
    ic.close();
    mc.close();
}

int main() {
    cout << "Pass2 Processing...\n\n";
    loadSymtab();
    loadLittab();
    cout << "\nProcessing IC file...\n\n";
    pass2();
    cout << "\n\nPass2 Completed! Check machine_code.txt\n";
    return 0;
}