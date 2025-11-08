#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class MNTEntry {
private:
    string name;
    int pp, kp, mdtp, kpdtp;

public:
    MNTEntry() : pp(0), kp(0), mdtp(0), kpdtp(0) {}
    
    MNTEntry(string n, int p, int k, int m, int kpd) 
        : name(n), pp(p), kp(k), mdtp(m), kpdtp(kpd) {}
    
    string getName() const { return name; }
    int getPp() const { return pp; }
    int getKp() const { return kp; }
    int getMdtp() const { return mdtp; }
    int getKpdtp() const { return kpdtp; }
};

vector<string> split(const string& str, char delimiter = ' ') {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

string removeChar(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return str;
}

int main() {
    ifstream irb, mdtb, kpdtb, mntb;
    ofstream fr, ala;
    
    try {
        // Open input files
        irb.open("intermediate.txt");
        mdtb.open("mdt.txt");
        kpdtb.open("kpdt.txt");
        mntb.open("mnt.txt");
        fr.open("pass2.txt");
        ala.open("ala.txt");
        
        if (!irb || !mdtb || !kpdtb || !mntb || !fr || !ala) {
            cerr << "Error opening files!" << endl;
            return 1;
        }
        
        // Data structures
        unordered_map<string, MNTEntry> mnt;
        unordered_map<int, string> aptab;
        unordered_map<string, int> aptabInverse;
        vector<string> mdt;
        vector<string> kpdt;
        
        // Read MDT
        string line;
        while (getline(mdtb, line)) {
            mdt.push_back(line);
        }
        
        // Read KPDT
        while (getline(kpdtb, line)) {
            kpdt.push_back(line);
        }
        
        // Read MNT
        while (getline(mntb, line)) {
            vector<string> parts = split(trim(line));
            if (parts.size() >= 5) {
                mnt[parts[0]] = MNTEntry(parts[0], 
                                        stoi(parts[1]), 
                                        stoi(parts[2]), 
                                        stoi(parts[3]), 
                                        stoi(parts[4]));
            }
        }
        
        // Process intermediate code
        while (getline(irb, line)) {
            vector<string> parts = split(trim(line));
            
            if (!parts.empty() && mnt.find(parts[0]) != mnt.end()) {
                aptab.clear();
                aptabInverse.clear();
                ala << "ALA for macro: " << parts[0] << endl;
                
                int pp = mnt[parts[0]].getPp();
                int kp = mnt[parts[0]].getKp();
                int kpdtp = mnt[parts[0]].getKpdtp();
                int mdtp = mnt[parts[0]].getMdtp();
                
                // Process positional parameters
                int paramNo = 1;
                for (int i = 0; i < pp && paramNo < parts.size(); i++) {
                    string param = removeChar(parts[paramNo], ',');
                    aptab[paramNo] = param;
                    aptabInverse["P" + to_string(paramNo)] = paramNo;
                    ala << paramNo << "\t" << param << endl;
                    paramNo++;
                }
                
                // Initialize keyword parameters with default values
                int j = kpdtp - 1;
                for (int i = 0; i < kp && j < kpdt.size(); i++) {
                    size_t tabPos = kpdt[j].find('\t');
                    if (tabPos != string::npos) {
                        string name = kpdt[j].substr(0, tabPos);
                        string value = kpdt[j].substr(tabPos + 1);
                        aptab[paramNo] = value;
                        aptabInverse[name] = paramNo;
                        ala << paramNo << "\t" << name << "\t" << value << endl;
                        paramNo++;
                    }
                    j++;
                }
                
                // Process keyword parameters in any order
                for (int i = pp + 1; i < parts.size(); i++) {
                    string param = removeChar(parts[i], ',');
                    size_t eqPos = param.find('=');
                    if (eqPos != string::npos) {
                        string name = removeChar(param.substr(0, eqPos), '&');
                        string value = param.substr(eqPos + 1);
                        if (aptabInverse.find(name) != aptabInverse.end()) {
                            int index = aptabInverse[name];
                            aptab[index] = value;
                            ala << index << "\t" << name << "\t" << value << endl;
                        }
                    }
                }
                
                // Process MDT entries
                int i = mdtp - 1;
                while (i < mdt.size() && trim(mdt[i]) != "MEND") {
                    vector<string> splits = split(trim(mdt[i]));
                    fr << "+";
                    for (const string& s : splits) {
                        if (s.find("(P,") != string::npos) {
                            string paramIndex = "";
                            for (char c : s) {
                                if (isdigit(c)) paramIndex += c;
                            }
                            if (!paramIndex.empty()) {
                                int index = stoi(paramIndex);
                                if (aptab.find(index) != aptab.end()) {
                                    fr << aptab[index] << "\t";
                                } else {
                                    fr << "null\t";
                                }
                            } else {
                                fr << s << "\t";
                            }
                        } else {
                            fr << s << "\t";
                        }
                    }
                    fr << endl;
                    i++;
                }
                ala << endl;
            } else {
                fr << line << endl;
            }
        }
        
        cout << "Pass 2 completed successfully!" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    // Close all files
    irb.close();
    mdtb.close();
    kpdtb.close();
    mntb.close();
    fr.close();
    ala.close();
    
    return 0;
}