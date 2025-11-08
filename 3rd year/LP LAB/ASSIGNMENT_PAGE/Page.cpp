#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void fifo(vector<int> pages, int f) {
    queue<int> q;
    int faults = 0;

    for (int p : pages) {
        bool found = false;
        queue<int> temp = q;
        while (!temp.empty()) {
            if (temp.front() == p) { found = true; break; }
            temp.pop();
        }

        if (!found) {
            if (q.size() == f) q.pop();
            q.push(p);
            faults++;
        }
    }

    cout << "FIFO Faults = " << faults << endl;
}

void lru(vector<int> pages, int f) {
    vector<int> list;
    int faults = 0;

    for (int p : pages) {
        auto it = find(list.begin(), list.end(), p);

        if (it == list.end()) {
            if (list.size() == f) list.erase(list.begin());
            list.push_back(p);
            faults++;
        } else {
            list.erase(it);
            list.push_back(p);
        }
    }
    cout << "LRU Faults = " << faults << endl;
}

void mru(vector<int> pages, int f) {
    vector<int> list;
    int faults = 0;

    for (int p : pages) {
        auto it = find(list.begin(), list.end(), p);

        if (it == list.end()) {
            if (list.size() == f) list.pop_back(); // remove MOST RECENTLY used
            list.push_back(p);
            faults++;
        } else {
            list.erase(it);
            list.push_back(p);
        }
    }
    cout << "MRU Faults = " << faults << endl;
}

void optimal(vector<int> pages, int f) {
    vector<int> list;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int p = pages[i];
        auto it = find(list.begin(), list.end(), p);    

        if (it == list.end()) {
            if (list.size() == f) {
                int idx = -1, farthest = -1;

                for (int x : list) {
                    int j;
                    for (j = i + 1; j < pages.size(); j++)
                        if (pages[j] == x) break;
                    
                    if (j > farthest) {
                        farthest = j;
                        idx = x;
                    }
                }
                list.erase(find(list.begin(), list.end(), idx));
            }
            list.push_back(p);
            faults++;
        }
    }

    cout << "Optimal Faults = " << faults << endl;
}

int main() {
    vector<int> pages = {7,0,1,2,0,3,0,4,2,3,0,3};
    int frames = 3;

    fifo(pages, frames);
    lru(pages, frames);
    mru(pages, frames);
    optimal(pages, frames);

    return 0;
}
