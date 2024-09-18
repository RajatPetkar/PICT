#include <iostream>
#include <string>
using namespace std;

class Job {
public:
    int jobId;
    string jobName;

    Job(int id, string name) {
        jobId = id;
        jobName = name;
    }
};

class JobQueue {
private:
    int front, rear;
    int maxSize;
    Job** queue; 

public:
    JobQueue(int size) {
        maxSize = size;
        queue = new Job*[maxSize];
        front = rear = -1;
    }

    ~JobQueue() {
        for (int i = 0; i <= rear; i++) {
            delete queue[i];
        }
        delete[] queue;
    }

    bool isFull() {
        return rear == maxSize - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void addJob(int id, string name) {
        if (isFull()) {
            cout << "Queue is full! Cannot add more jobs." << endl;
            return;
        }

        if (front == -1) front = 0; 

        queue[++rear] = new Job(id, name);  
        cout << "Job added: " << name << " (ID: " << id << ")" << endl;
    }

    void deleteJob() {
        if (isEmpty()) {
            cout << "Queue is empty! No jobs to delete." << endl;
            return;
        }

        cout << "Job deleted: " << queue[front]->jobName << " (ID: " << queue[front]->jobId << ")" << endl;
        delete queue[front];  
        front++;
    }

    void displayJobs() {
        if (isEmpty()) {
            cout << "Queue is empty! No jobs to display." << endl;
            return;
        }

        cout << "Current Jobs in Queue:" << endl;
        for (int i = front; i <= rear; i++) {
            cout << queue[i]->jobName << " (ID: " << queue[i]->jobId << ")" << endl;
        }
    }
};

int main() {
    int queueSize;
    cout << "Enter the size of the Job Queue: ";
    cin >> queueSize;

    JobQueue jobQueue(queueSize);

    int choice, id;
    string name;

    do {
        cout << "\nJob Queue Menu:" << endl;
        cout << "1. Add Job" << endl;
        cout << "2. Delete Job" << endl;
        cout << "3. Display Jobs" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Job ID: ";
            cin >> id;
            cout << "Enter Job Name: ";
            cin >> name;
            jobQueue.addJob(id, name);
            break;

        case 2:
            jobQueue.deleteJob();
            break;

        case 3:
            jobQueue.displayJobs();
            break;

        case 4:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "AANDHA HAI KYA !!!" << endl;
        }
    } while (choice != 4);

    return 0;
}
