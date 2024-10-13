#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

template <typename T>
class PriorityItem {
public:
    T data;      
    int priority; 

    PriorityItem(T d, int p) : data(d), priority(p) {}

    bool operator<=(const PriorityItem<T>& other) const {
        return this->priority <= other.priority;
    }
};

template <typename T>
class PriorityQueue {
private:
    vector<PriorityItem<T>> queue; 

public:
    void insert(const T& item, int priority) {
        PriorityItem<T> newItem(item, priority);  
        queue.push_back(newItem);                 
        sort(queue.begin(), queue.end(), [](const PriorityItem<T>& a, const PriorityItem<T>& b) {
            return a.priority < b.priority; 
        });
    }

    T remove() {
        if (queue.empty()) {
            throw out_of_range("Priority queue is empty!");
        }

        T highestPriorityItem = queue.front().data;
        queue.erase(queue.begin());
        return highestPriorityItem;
    }

    bool isEmpty() const {
        return queue.empty();
    }

    void display() const {
        if (queue.empty()) {
            cout << "Priority queue is empty!" << endl;
            return;
        }

        cout << "Priority Queue (Data, Priority):" << endl;
        for (const auto& item : queue) {
            cout << "(" << item.data << ", " << item.priority << ") ";
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue<string> pq; 

    pq.insert("Task A", 2);   
    pq.insert("Task B", 5);
    pq.insert("Task C", 1);
    pq.insert("Task D", 4);

    pq.display();

    cout << "Removed: " << pq.remove() << endl;
    pq.display();

    cout << "Removed: " << pq.remove() << endl;
    pq.display();

    return 0;
}
