#include <iostream>
using namespace std;

void firstFit(int b[], int blen, int p[], int plen) {
    cout << "\nFirst Fit:\n";
    for (int i = 0; i < plen; i++) {
        bool placed = false;
        for (int j = 0; j < blen; j++) {
            if (b[j] >= p[i]) {
                cout << "Process " << p[i] << " in Block " << b[j] << endl;
                b[j] -= p[i];
                placed = true;
                break;
            }
        }
        if (!placed) cout << "Process " << p[i] << " Not Allocated\n";
    }
}

void bestFit(int b[], int blen, int p[], int plen) {
    cout << "\nBest Fit:\n";
    for (int i = 0; i < plen; i++) {
        int idx = -1;
        for (int j = 0; j < blen; j++) {
            if (b[j] >= p[i] && (idx == -1 || b[j] < b[idx])) {
                idx = j;
            }
        }
        if (idx != -1) {
            cout << "Process " << p[i] << " in Block " << b[idx] << endl;
            b[idx] -= p[i];
        } else {
            cout << "Process " << p[i] << " Not Allocated\n";
        }
    }
}

void worstFit(int b[], int blen, int p[], int plen) {
    cout << "\nWorst Fit:\n";
    for (int i = 0; i < plen; i++) {
        int idx = -1;
        for (int j = 0; j < blen; j++) {
            if (b[j] >= p[i] && (idx == -1 || b[j] > b[idx])) {
                idx = j;
            }
        }
        if (idx != -1) {
            cout << "Process " << p[i] << " in Block " << b[idx] << endl;
            b[idx] -= p[i];
        } else {
            cout << "Process " << p[i] << " Not Allocated\n";
        }
    }
}

void nextFit(int b[], int blen, int p[], int plen) {
    cout << "\nNext Fit:\n";
    int pos = 0;
    for (int i = 0; i < plen; i++) {
        bool placed = false;
        for (int j = 0; j < blen; j++) {
            int idx = (pos + j) % blen;
            if (b[idx] >= p[i]) {
                cout << "Process " << p[i] << " in Block " << b[idx] << endl;
                b[idx] -= p[i];
                pos = idx;
                placed = true;
                break;
            }
        }
        if (!placed) cout << "Process " << p[i] << " Not Allocated\n";
    }
}

int main() {
    int blocks[] = {100, 500, 200, 300, 600};
    int process[] = {212, 417, 112, 426};
    int blen = 5, plen = 4;

    firstFit((int[]) {100, 500, 200, 300, 600}, blen, process, plen);
    bestFit((int[]) {100, 500, 200, 300, 600}, blen, process, plen);
    worstFit((int[]) {100, 500, 200, 300, 600}, blen, process, plen);
    nextFit((int[]) {100, 500, 200, 300, 600}, blen, process, plen);

    return 0;
}