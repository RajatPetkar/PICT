#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    ifstream mntFile("mnt.txt");
    ifstream mdtFile("mdt.txt");
    ifstream kpdtFile("kpdt.txt");
    ifstream pntFile("pntab.txt");
    ifstream irFile("intermediate.txt");
    ofstream expandedFile("expanded_output.txt");

    map<string, vector<string>> MDT;    // Macro Name → List of MDT entries
    map<string, vector<string>> PNTAB;  // Macro Name → Parameter list
    map<string, int> MNT;               // Macro Name → MDT starting index
    map<string, string> KPDT;          // Parameter → Default Value

    // 1️⃣ Load MNT
    string line;
    while (getline(mntFile, line)) {
        stringstream ss(line);
        string macroName;
        int pp, kp, mdtp, kpdtp;
        ss >> macroName >> pp >> kp >> mdtp >> kpdtp;
        MNT[macroName] = mdtp;
    }
    mntFile.close();

    // 2️⃣ Load PNTAB
    while (getline(pntFile, line)) {
        stringstream ss(line);
        string macroName, param;
        ss >> macroName;  // macroName:
        macroName.pop_back();  // Remove colon (:)

        vector<string> paramList;
        while (ss >> param) {
            paramList.push_back(param);
        }

        PNTAB[macroName] = paramList;
    }
    pntFile.close();

    // 3️⃣ Load KPDT
    while (getline(kpdtFile, line)) {
        stringstream ss(line);
        string paramName, defaultValue;
        ss >> paramName >> defaultValue;
        KPDT[paramName] = defaultValue;
    }
    kpdtFile.close();

    // 4️⃣ Load MDT
    vector<string> allMDT;
    while (getline(mdtFile, line)) {
        allMDT.push_back(line);
    }
    mdtFile.close();

    // 5️⃣ Process Intermediate file
    while (getline(irFile, line)) {
        stringstream ss(line);
        vector<string> parts;
        string word;
        ss >> word;
        parts.push_back(word);

        // If macro call detected
        if (MNT.find(parts[0]) != MNT.end()) {
            string macroName = parts[0];
            vector<string> actualArgs;

            // Read actual arguments
            while (ss >> word) {
                // Split arguments by comma
                stringstream args(word);
                string arg;
                while (getline(args, arg, ',')) {
                    actualArgs.push_back(arg);
                }
            }

            vector<string> paramList = PNTAB[macroName];
            map<int, string> argumentMap;

            // Fill actual arguments first
            for (size_t i = 0; i < actualArgs.size(); i++) {
                argumentMap[i + 1] = actualArgs[i];
            }

            // Fill default arguments from KPDT if not supplied
            for (size_t i = actualArgs.size(); i < paramList.size(); i++) {
                string paramName = paramList[i];
                argumentMap[i + 1] = KPDT[paramName];
            }

            int mdtIndex = MNT[macroName] - 1;  // MDT indexing starts from 1 in MNT

            while (true) {
                string mdtLine = allMDT[mdtIndex];
                if (mdtLine == "MEND") break;

                stringstream mdtSS(mdtLine);
                string token;

                while (mdtSS >> token) {
                    if (token.find("(P,") != string::npos) {
                        int paramPos = stoi(token.substr(3, token.length() - 4));
                        expandedFile << argumentMap[paramPos] << "\t";
                    } else {
                        expandedFile << token << "\t";
                    }
                }
                expandedFile << "\n";
                mdtIndex++;
            }
        } else {
            // Non-macro line is written directly
            expandedFile << line << "\n";
        }
    }

    irFile.close();
    expandedFile.close();

    cout << "\n\t Macro Expansion (Pass 2) Executed Successfully ...!!" << endl;

    return 0;
}
