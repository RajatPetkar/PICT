#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>  
using namespace std;

int main() {
    ifstream br("macro_input.asm");
    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream pnt("pntab.txt");
    ofstream ir("intermediate.txt");

    map<string, int> pntab;
    string line, macroName;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(br, line)) {
        stringstream ss(line);
        vector<string> parts;
        string word;
        while (ss >> word) parts.push_back(word);

        if (parts.size() == 0) continue;

        if (parts[0] == "MACRO" || parts[0] == "macro") {
            flag = 1;
            getline(br, line);
            stringstream ss2(line);
            parts.clear();
            while (ss2 >> word) parts.push_back(word);

            macroName = parts[0];

            if (parts.size() <= 1) {
                mnt << parts[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t"
                    << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
                continue;
            }

            for (int i = 1; i < parts.size(); i++) {
                string param = parts[i];
                param.erase(remove(param.begin(), param.end(), '&'), param.end());
                param.erase(remove(param.begin(), param.end(), ','), param.end());

                if (param.find('=') != string::npos) {
                    kp++;
                    string pName = param.substr(0, param.find('='));
                    string pVal = param.substr(param.find('=') + 1);
                    pntab[pName] = paramNo++;
                    if (pVal != "")
                        kpdt << pName << "\t" << pVal << "\n";
                    else
                        kpdt << pName << "\t-\n";
                } else {
                    pntab[param] = paramNo++;
                    pp++;
                }
            }

            mnt << parts[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t"
                << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
            kpdtp += kp;
        }
        else if (parts[0] == "MEND") {
            mdt << line << "\n";
            flag = kp = pp = 0;
            mdtp++;
            paramNo = 1;

            pnt << macroName << ":\t";
            for (auto &x : pntab)
                pnt << x.first << "\t";
            pnt << "\n";
            pntab.clear();
        }
        else if (flag == 1) {
            for (int i = 0; i < parts.size(); i++) {
                if (parts[i].find('&') != string::npos) {
                    string param = parts[i];
                    param.erase(remove(param.begin(), param.end(), '&'), param.end());
                    param.erase(remove(param.begin(), param.end(), ','), param.end());
                    mdt << "(P," << pntab[param] << ")\t";
                } else {
                    mdt << parts[i] << "\t";
                }
            }
            mdt << "\n";
            mdtp++;
        }
        else {
            ir << line << "\n";
        }
    }

    br.close();
    mdt.close();
    mnt.close();
    ir.close();
    pnt.close();
    kpdt.close();
    cout << "Macro Pass1 Processing done. :)" << endl;
    return 0;
}
