#include <iostream>
#include <thread>
#include <queue>
using namespace std;

class ProducerConsumer {
public:
    int bufferSize;
    queue<int> buffer;
    bool mutex;
    int e, f; 

    ProducerConsumer(int size) {
        bufferSize = size;
        e = size;  
        f = 0;     
        mutex = true;
    }

    void wait(int &sem) {
        while (sem <= 0);
        sem--;
    }

    void signal(int &sem) {
        sem++;
    }

    void lock() {
        while (!mutex);
        mutex = false;
    }

    void unlock() {
        mutex = true;
    }

    void produce(int item) {
        wait(e);
        lock();

        buffer.push(item);
        cout << "Produced: " << item << endl;

        unlock();
        signal(f);
    }

    void consume() {
        wait(f);
        lock();

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        unlock();
        signal(e);
    }

    bool isFull() {
        return buffer.size() == bufferSize;
    }

    bool isEmpty() {
        return buffer.empty();
    }
};


void producerThread(ProducerConsumer &pc, int n) {
    int item = 1;
    while (item <= n) {
        if (!pc.isFull()) {
            pc.produce(item++);
        }
    }
}


void consumerThread(ProducerConsumer &pc, int n) {
    int consumed = 0;
    while (consumed < n) {
        if (!pc.isEmpty()) {
            pc.consume();
            consumed++;
        }
    }
}

int main() {
    int bufferSize, totalItems;
    cout << "Enter buffer size: ";
    cin >> bufferSize;
    cout << "Enter how many items to produce/consume: ";
    cin >> totalItems;

    ProducerConsumer pc(bufferSize);

    thread prod(producerThread, ref(pc), totalItems);
    thread cons(consumerThread, ref(pc), totalItems);

    prod.join();
    cons.join();

    return 0;
}
