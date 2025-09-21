#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

// MNT Entry
struct MNTEntry {
    string name;
    int mdtIndex;
    int paramCount;
    
    MNTEntry(string n, int mdt, int pc) : name(n), mdtIndex(mdt), paramCount(pc) {}
};

// MDT Entry  
struct MDTEntry {
    string statement;
    
    MDTEntry(string s) : statement(s) {}
};

vector<MNTEntry> MNT;
vector<MDTEntry> MDT;
map<string, int> macroMap; // macro name to MNT index

vector<string> tokenize(string line) {
    vector<string> tokens;
    istringstream iss(line);
    string token;
    while(iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void expandMacro(string macroName, vector<string>& actualParams, ofstream& output) {
    int mntIndex = macroMap[macroName];
    int mdtStart = MNT[mntIndex].mdtIndex;
    int paramCount = MNT[mntIndex].paramCount;
    
    cout << "Expanding macro: " << macroName << "\n";
    
    // Expand macro from MDT
    for(int i = mdtStart; i < MDT.size(); i++) {
        if(MDT[i].statement == "MEND") break;
        
        string expandedLine = "";
        istringstream iss(MDT[i].statement);
        string token;
        
        while(iss >> token) {
            if(token[0] == '#') {
                // Replace parameter
                int paramIndex = stoi(token.substr(1));
                if(paramIndex < actualParams.size()) {
                    expandedLine += actualParams[paramIndex];
                }
            } else {
                expandedLine += token;
            }
            expandedLine += " ";
        }
        
        output << expandedLine << "\n";
        cout << "  Expanded: " << expandedLine << "\n";
    }
}

int main() {
    // Load MNT
    ifstream mntFile("mnt.txt");
    string name;
    int mdtIndex, paramCount;
    int mntIndex = 0;
    
    while(mntFile >> name >> mdtIndex >> paramCount) {
        MNT.push_back(MNTEntry(name, mdtIndex, paramCount));
        macroMap[name] = mntIndex++;
    }
    mntFile.close();
    
    // Load MDT
    ifstream mdtFile("mdt.txt");
    int index;
    string statement;
    string line;
    
    while(getline(mdtFile, line)) {
        if(line.empty()) continue;
        size_t pos = line.find(' ');
        if(pos != string::npos) {
            statement = line.substr(pos + 1);
            MDT.push_back(MDTEntry(statement));
        }
    }
    mdtFile.close();
    
    // Process intermediate code
    ifstream intermediate("intermediate.txt");
    ofstream output("output.txt");
    
    cout << "MACRO PASS 2 OUTPUT:\n";
    cout << "Processing intermediate code...\n\n";
    
    string inputLine;
    int lineNo = 0;
    
    while(getline(intermediate, inputLine)) {
        lineNo++;
        if(inputLine.empty()) {
            output << "\n";
            continue;
        }
        
        vector<string> tokens = tokenize(inputLine);
        if(tokens.empty()) continue;
        
        // Check if first token is a macro call
        if(macroMap.find(tokens[0]) != macroMap.end()) {
            // Macro call found
            vector<string> actualParams;
            for(int i = 1; i < tokens.size(); i++) {
                actualParams.push_back(tokens[i]);
            }
            
            cout << "Line " << lineNo << ": Macro call found - " << tokens[0] << "\n";
            expandMacro(tokens[0], actualParams, output);
        }
        else {
            // Regular statement, copy as is
            output << inputLine << "\n";
            cout << "Line " << lineNo << ": Copied - " << inputLine << "\n";
        }
    }
    
    intermediate.close();
    output.close();
    
    cout << "\nPass 2 completed. Expanded code saved in output.txt\n";
    
    return 0;
}