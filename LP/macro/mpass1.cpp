#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

// Macro Name Table (MNT) Entry
struct MNTEntry {
    string name;
    int mdtIndex;
    int paramCount;
    
    MNTEntry(string n, int mdt, int pc) : name(n), mdtIndex(mdt), paramCount(pc) {}
};

// Macro Definition Table (MDT) Entry
struct MDTEntry {
    string statement;
    
    MDTEntry(string s) : statement(s) {}
};

vector<MNTEntry> MNT;
vector<MDTEntry> MDT;
map<string, int> paramMap; // For current macro parameters

bool isInsideMacro = false;
string currentMacro = "";
int mdtIndex = 0;

vector<string> tokenize(string line) {
    vector<string> tokens;
    istringstream iss(line);
    string token;
    while(iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream input("input.txt");
    ofstream intermediate("intermediate.txt");
    ofstream mntFile("mnt.txt");
    ofstream mdtFile("mdt.txt");
    
    string line;
    int lineNo = 0;
    
    cout << "MACRO PASS 1 OUTPUT:\n";
    cout << "Line\tProcessing\n";
    cout << "-------------------------\n";
    
    while(getline(input, line)) {
        lineNo++;
        if(line.empty()) continue;
        
        vector<string> tokens = tokenize(line);
        if(tokens.empty()) continue;
        
        // Check for MACRO definition start
        if(tokens.size() >= 2 && tokens[1] == "MACRO") {
            isInsideMacro = true;
            currentMacro = tokens[0];
            
            // Process parameters
            paramMap.clear();
            int paramCount = 0;
            for(int i = 2; i < tokens.size(); i++) {
                paramMap[tokens[i]] = paramCount++;
            }
            
            // Add to MNT
            MNT.push_back(MNTEntry(currentMacro, mdtIndex, paramCount));
            
            cout << lineNo << "\tMacro Definition Start: " << currentMacro << "\n";
            continue;
        }
        
        // Check for MEND (Macro End)
        if(tokens[0] == "MEND") {
            if(isInsideMacro) {
                MDT.push_back(MDTEntry("MEND"));
                mdtIndex++;
                isInsideMacro = false;
                currentMacro = "";
                cout << lineNo << "\tMacro Definition End\n";
            }
            continue;
        }
        
        // If inside macro definition, add to MDT
        if(isInsideMacro) {
            string mdtEntry = "";
            for(int i = 0; i < tokens.size(); i++) {
                // Replace parameters with positional notation
                if(paramMap.find(tokens[i]) != paramMap.end()) {
                    mdtEntry += "#" + to_string(paramMap[tokens[i]]);
                } else {
                    mdtEntry += tokens[i];
                }
                if(i < tokens.size() - 1) mdtEntry += " ";
            }
            
            MDT.push_back(MDTEntry(mdtEntry));
            mdtIndex++;
            cout << lineNo << "\tAdded to MDT: " << mdtEntry << "\n";
        }
        // If not inside macro, write to intermediate file
        else {
            intermediate << line << "\n";
            cout << lineNo << "\tCopied to intermediate\n";
        }
    }
    
    // Save MNT
    for(int i = 0; i < MNT.size(); i++) {
        mntFile << MNT[i].name << " " << MNT[i].mdtIndex 
               << " " << MNT[i].paramCount << "\n";
    }
    
    // Save MDT
    for(int i = 0; i < MDT.size(); i++) {
        mdtFile << i << " " << MDT[i].statement << "\n";
    }
    
    // Display tables
    cout << "\nMACRO NAME TABLE (MNT):\n";
    cout << "Name\tMDT Index\tParam Count\n";
    cout << "--------------------------------\n";
    for(auto& entry : MNT) {
        cout << entry.name << "\t" << entry.mdtIndex 
             << "\t\t" << entry.paramCount << "\n";
    }
    
    cout << "\nMACRO DEFINITION TABLE (MDT):\n";
    cout << "Index\tStatement\n";
    cout << "------------------------\n";
    for(int i = 0; i < MDT.size(); i++) {
        cout << i << "\t" << MDT[i].statement << "\n";
    }
    
    input.close();
    intermediate.close();
    mntFile.close();
    mdtFile.close();
    
    cout << "\nPass 1 completed. Files created: intermediate.txt, mnt.txt, mdt.txt\n";
    
    return 0;
}
