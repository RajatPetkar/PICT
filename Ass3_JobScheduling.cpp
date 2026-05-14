#include <bits/stdc++.h>
using namespace std;
struct Job {
    char id;
    int deadline;
    int profit;
};
// Comparator for sorting by profit
bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;
    Job arr[n];

    cout << "\nEnter Job ID Deadline Profit\n";
    for(int i = 0; i < n; i++) {
        cin >> arr[i].id
            >> arr[i].deadline
            >> arr[i].profit;
    }
    // Sort jobs by maximum profit
    sort(arr, arr + n, cmp);

    // Find maximum deadline
    int maxDeadline = 0;
    for(int i = 0; i < n; i++) {
        maxDeadline = max(maxDeadline,arr[i].deadline);
    }
    // Slot array
    vector<char> slot(maxDeadline, 0);
    int totalProfit = 0;
    // Job Scheduling
    for(int i = 0; i < n; i++) {
        for(int j = arr[i].deadline - 1;j >= 0;j--) {
            if(slot[j] == 0) {
                slot[j] = arr[i].id;
                totalProfit += arr[i].profit;
                break;
            }
        }
    }
    // Output scheduled jobs
    cout << "\nScheduled Jobs:\n";

    for(int i = 0; i < maxDeadline; i++) {
        if(slot[i] != 0)
            cout << slot[i] << " ";
    }
    cout << "\n\nTotal Profit = "
         << totalProfit;

    return 0;
}
