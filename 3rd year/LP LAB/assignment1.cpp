#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid, arrival, burst, priority;
    int remaining, start = -1, waiting = 0, turnaround = 0, complete = 0;
};

void printResult(vector<Process> p) {
    float totalWT = 0, totalTAT = 0;
    cout << "\nPID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (auto& pr : p) {
        cout << pr.pid << "\t" << pr.arrival << "\t" << pr.burst << "\t" << pr.priority
             << "\t\t" << pr.waiting << "\t" << pr.turnaround << "\n";
        totalWT += pr.waiting;
        totalTAT += pr.turnaround;
    }
    int n = p.size();
    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << "\n";
}

bool arrivalCompare(Process a, Process b) {
    return a.arrival < b.arrival;
}

void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), arrivalCompare);
    int time = 0;
    for (auto& pr : p) {
        if (time < pr.arrival) time = pr.arrival;
        pr.waiting = time - pr.arrival;
        time += pr.burst;
        pr.turnaround = pr.waiting + pr.burst;
    }
    printResult(p);
}

void sjf(vector<Process> p) {
    int n = p.size(), complete = 0, time = 0;
    for (auto& pr : p) pr.remaining = pr.burst;
    while (complete < n) {
        int idx = -1, minBurst = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minBurst) {
                minBurst = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        p[idx].remaining--;
        time++;
        if (p[idx].remaining == 0) {
            complete++;
            p[idx].complete = time;
            p[idx].turnaround = p[idx].complete - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }
    printResult(p);
}

void priority(vector<Process> p) {
    int n = p.size(), complete = 0, time = 0;
    for (auto& pr : p) pr.remaining = pr.burst;
    while (complete < n) {
        int idx = -1, best = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        p[idx].remaining--;
        time++;
        if (p[idx].remaining == 0) {
            complete++;
            p[idx].complete = time;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }
    printResult(p);
}

// void roundRobin(vector<Process> p, int quantum) {
//     int n = p.size(), time = 0, complete = 0;
//     queue<int> q;
//     vector<bool> inQ(n, false);
//     for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

//     sort(p.begin(), p.end(),arrivalCompare);

//     q.push(0); inQ[0] = true;

//     while (complete < n) {
//         if (q.empty()) {
//             for (int i = 0; i < n; i++) {
//                 if (p[i].remaining > 0 && p[i].arrival > time) {
//                     time = p[i].arrival;
//                     q.push(i);
//                     inQ[i] = true;
//                     break;
//                 }
//             }
//             continue;
//         }

//         int i = q.front(); q.pop();
//         int run = min(quantum, p[i].remaining);
//         p[i].remaining -= run;
//         time += run;

//         for (int j = 0; j < n; j++) {
//             if (!inQ[j] && p[j].arrival <= time && p[j].remaining > 0) {
//                 q.push(j);
//                 inQ[j] = true;
//             }
//         }

//         if (p[i].remaining > 0) {
//             q.push(i);
//         } else {
//             p[i].complete = time;
//             p[i].turnaround = time - p[i].arrival;
//             p[i].waiting = p[i].turnaround - p[i].burst;
//             complete++;
//         }
//     }

//     printResult(p);
// }

int main() {
    int n, choice, quantum;
    vector<Process> p;
    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Process temp;
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "PID: "; cin >> temp.pid;
        cout << "Arrival Time: "; cin >> temp.arrival;
        cout << "Burst Time: "; cin >> temp.burst;
        cout << "Priority (lower is better): "; cin >> temp.priority;
        p.push_back(temp);
    }

    cout << "Enter time slice for Round Robin: ";
    cin >> quantum;

    do {
        cout << "\nMenu:\n1. FCFS\n2. SJF (Preemptive)\n3. Priority (Preemptive)\n4. Round Robin\n5. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: fcfs(p); break;
            case 2: sjf(p); break;
            case 3: priority(p); break;
            // case 4: roundRobin(p, quantum); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}
