#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>  // Important for std::remove

using namespace std;

int main() {
    ifstream infile("input.txt");
    ofstream mntFile("mnt.txt");
    ofstream mdtFile("mdt.txt");
    ofstream kpdtFile("kpdt.txt");
    ofstream pntFile("pntab.txt");
    ofstream irFile("intermediate.txt");

    string line;
    string macroName;
    map<string, int> pntab;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> parts;
        string word;

        while (ss >> word) {
            parts.push_back(word);
        }

        if (parts.empty()) continue;

        if (parts[0] == "MACRO") {
            flag = 1;
            getline(infile, line);
            stringstream ss2(line);
            parts.clear();
            while (ss2 >> word) {
                parts.push_back(word);
            }

            macroName = parts[0];
            if (parts.size() <= 1) {
                mntFile << parts[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" 
                        << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
                continue;
            }

            for (size_t i = 1; i < parts.size(); i++) {
                // Properly remove '&' and ',' characters
                parts[i].erase(std::remove(parts[i].begin(), parts[i].end(), '&'), parts[i].end());
                parts[i].erase(std::remove(parts[i].begin(), parts[i].end(), ','), parts[i].end());

                if (parts[i].find('=') != string::npos) {
                    ++kp;
                    size_t eqPos = parts[i].find('=');
                    string key = parts[i].substr(0, eqPos);
                    string value = parts[i].substr(eqPos + 1);

                    pntab[key] = paramNo++;
                    kpdtFile << key << "\t" << (value.empty() ? "-" : value) << "\n";
                } else {
                    pntab[parts[i]] = paramNo++;
                    ++pp;
                }
            }

            mntFile << parts[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" 
                    << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";

            kpdtp += kp;
        } else if (parts[0] == "MEND") {
            mdtFile << line << "\n";
            flag = kp = pp = 0;
            mdtp++;
            paramNo = 1;

            pntFile << macroName << ":\t";
            for (auto &entry : pntab) {
                pntFile << entry.first << "\t";
            }
            pntFile << "\n";
            pntab.clear();
        } else if (flag == 1) {
            for (auto &part : parts) {
                if (part.find('&') != string::npos) {
                    part.erase(std::remove(part.begin(), part.end(), '&'), part.end());
                    mdtFile << "(P," << pntab[part] << ")\t";
                } else {
                    mdtFile << part << "\t";
                }
            }
            mdtFile << "\n";
            mdtp++;
        } else {
            irFile << line << "\n";
        }
    }

    infile.close();
    mntFile.close();
    mdtFile.close();
    kpdtFile.close();
    pntFile.close();
    irFile.close();

    cout << "\n\t Executed Successfully ...!!" << endl;

    return 0;
}
