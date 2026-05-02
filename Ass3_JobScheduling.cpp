#include <bits/stdc++.h>
using namespace std;

struct Job {
    char id;
    int deadline, profit;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    Job arr[] = {{'A',4,100}, {'B',1,190}, {'C',3,27}, {'D',2,25}};
    int n = 4;

    sort(arr, arr+n, cmp);

    int slot[3] = {0};

    for(int i = 0; i < n; i++) {
        for(int j = arr[i].deadline-1; j >= 0; j--) {
            if(slot[j] == 0) {
                slot[j] = arr[i].id;
                break;
            }
        }
    }

    for(int i = 0; i < 3; i++)
        if(slot[i]) cout << (char)slot[i] << " ";
}