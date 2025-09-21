
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int completion;
    int turnaround;
    int waiting;
    int remaining;
    
    Process(int p, int a, int b, int pr = 0) 
        : pid(p), arrival(a), burst(b), priority(pr), remaining(b) {}
};

void displayResults(vector<Process>& processes, string algorithm) {
    cout << "\n" << algorithm << " Results:\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "--------------------------------\n";
    
    float avgTAT = 0, avgWT = 0;
    
    for(auto& p : processes) {
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
        avgTAT += p.turnaround;
        avgWT += p.waiting;
        
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }
    
    cout << "Average TAT: " << avgTAT/processes.size() << endl;
    cout << "Average WT: " << avgWT/processes.size() << endl;
}

// FCFS Algorithm
void fcfs(vector<Process> processes) {
    sort(processes.begin(), processes.end(), 
         [](const Process& a, const Process& b) {
             return a.arrival < b.arrival;
         });
    
    int currentTime = 0;
    
    for(auto& p : processes) {
        if(currentTime < p.arrival) {
            currentTime = p.arrival;
        }
        currentTime += p.burst;
        p.completion = currentTime;
    }
    
    displayResults(processes, "FCFS");
}

// SJF Preemptive (SRTF)
void sjfPreemptive(vector<Process> processes) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;
    
    while(completed < n) {
        int shortest = -1;
        int minBurst = 999999;
        
        // Find process with shortest remaining time
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival <= currentTime && 
               processes[i].remaining > 0 && 
               processes[i].remaining < minBurst) {
                minBurst = processes[i].remaining;
                shortest = i;
            }
        }
        
        if(shortest == -1) {
            currentTime++;
            continue;
        }
        
        processes[shortest].remaining--;
        currentTime++;
        
        if(processes[shortest].remaining == 0) {
            processes[shortest].completion = currentTime;
            completed++;
        }
    }
    
    displayResults(processes, "SJF Preemptive (SRTF)");
}

// Priority Non-Preemptive
void priorityNonPreemptive(vector<Process> processes) {
    sort(processes.begin(), processes.end(),
         [](const Process& a, const Process& b) {
             return a.arrival < b.arrival;
         });
    
    int currentTime = 0;
    vector<bool> completed(processes.size(), false);
    
    for(int i = 0; i < processes.size(); i++) {
        int highestPriority = -1;
        int minPriority = 9999999;
        
        // Find highest priority process that has arrived
        for(int j = 0; j < processes.size(); j++) {
            if(!completed[j] && processes[j].arrival <= currentTime && 
               processes[j].priority < minPriority) {
                minPriority = processes[j].priority;
                highestPriority = j;
            }
        }
        
        if(highestPriority == -1) {
            currentTime++;
            i--;
            continue;
        }
        
        if(currentTime < processes[highestPriority].arrival) {
            currentTime = processes[highestPriority].arrival;
        }
        
        currentTime += processes[highestPriority].burst;
        processes[highestPriority].completion = currentTime;
        completed[highestPriority] = true;
    }
    
    displayResults(processes, "Priority Non-Preemptive");
}

// Round Robin
void roundRobin(vector<Process> processes, int quantum) {
    queue<int> readyQueue;
    int currentTime = 0;
    int n = processes.size();
    
    // Add first process
    readyQueue.push(0);
    vector<bool> inQueue(n, false);
    inQueue[0] = true;
    
    while(!readyQueue.empty()) {
        int current = readyQueue.front();
        readyQueue.pop();
        inQueue[current] = false;
        
        if(processes[current].remaining <= quantum) {
            currentTime += processes[current].remaining;
            processes[current].remaining = 0;
            processes[current].completion = currentTime;
        } else {
            currentTime += quantum;
            processes[current].remaining -= quantum;
        }
        
        // Add newly arrived processes
        for(int i = 0; i < n; i++) {
            if(!inQueue[i] && processes[i].remaining > 0 && 
               processes[i].arrival <= currentTime) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }
        
        // Re-add current process if not finished
        if(processes[current].remaining > 0) {
            readyQueue.push(current);
            inQueue[current] = true;
        }
    }
    
    displayResults(processes, "Round Robin (Quantum=" + to_string(quantum) + ")");
}

int main() {
    cout << "=== CPU SCHEDULING ALGORITHMS ===\n";
    
    vector<Process> processes = {
        Process(1, 0, 8, 2),
        Process(2, 1, 4, 1),
        Process(3, 2, 9, 3),
        Process(4, 3, 5, 2)
    };
    
    cout << "Input Processes:\n";
    cout << "PID\tAT\tBT\tPriority\n";
    for(auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority << "\n";
    }
    
    fcfs(processes);
    
    // Reset remaining time for other algorithms
    for(auto& p : processes) p.remaining = p.burst;
    sjfPreemptive(processes);
    
    for(auto& p : processes) p.remaining = p.burst;
    priorityNonPreemptive(processes);
    
    for(auto& p : processes) p.remaining = p.burst;
    roundRobin(processes, 3);
    
    return 0;
}