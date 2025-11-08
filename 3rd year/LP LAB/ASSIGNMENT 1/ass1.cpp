#include <iostream>
using namespace std;

class Semaphore
{
public:
    int val;
    Semaphore(int i)
    {
        val = i;
    }

    bool wait()
    {
        if (val > 0)
        {
            val--;
            return true;
        }
        return false;   
    }

    void signal()
    {
        val++;
    }
};

int main()
{   
    Semaphore empty(10);
    Semaphore mutex(1);
    Semaphore full(0);
    int buffer[10];
    int in = 0;
    int out = 0;
    int count = 0;

    while (true)
    {
        int choice;
        cout << "Enter operation: \n1.produce \n2.Consume\n3.Show Semaphores\n4.Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (!empty.wait())
            {
                cout << "Buffer is full, cannot perform wait on empty semaphore." << endl;
                break;
            }
            else if (!mutex.wait())
            {
                cout << "Resource is busy, cannot perform wait on mutex semaphore." << endl;
                empty.signal();
                break;
            }   
            else
            {
                cout << "enter item to produce: ";
                int item;
                cin >> item;
                buffer[in] = item;
                in = (in + 1) % 10;
                count++;
                cout << "Produced item: " << item << endl;

                mutex.signal();
                full.signal();
                break;
            }

        case 2:
            if (!full.wait())
            {
                cout << "Buffer is empty, cannot perform wait on full semaphore." << endl;
                break;
            }
            else if (!mutex.wait())
            {
                cout << "Resource is busy, cannot perform wait on mutex semaphore." << endl;
                full.signal();
                break;
            }
            else
            {
                int item = buffer[out];
                out = (out + 1) % 10;
                count--;
                cout << "Consumed item: " << item << endl;

                mutex.signal();
                empty.signal();
                break;
            }

        case 3:
            cout << "Semaphore values - Empty: " << empty.val << ", Mutex: " << mutex.val << ", Full: " << full.val << endl;
            break;
        case 4:
            return 0;
        }
    }
}