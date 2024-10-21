#include <iostream>
using namespace std;

template <typename T>
class Temp{
    T *arr;
    int capacity;
public:
    Temp(){
        cout << "Enter size of the array: ";
        cin >> this->capacity;
        arr = new T[capacity];
        cout << "Enter the elements of the array" << endl;
        for(int i = 0; i < capacity; i++){
            T element;
            cout << "Enter element: ";
            cin >> element;
            arr[i] = element;
        }        
    }

    void swap(int i1, int i2){
        T temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }

    void display(){
        for(int i = 0; i < capacity; i++){
            cout << arr[i] << "\t";
        }
    }
    
    void selectionsort(){
        for(int i = 0; i < capacity - 1; i++){
            int minindex = i;
            for(int j = i + 1; j < capacity; j++){
                if(arr[j] < arr[minindex]){
                    minindex = j;
                }
            }
            this->swap(i, minindex);
        }
        this->display();        
    }

    void insertionsort(){
        int i, key, j;
        for (i = 1; i < capacity; i++) {
            key = arr[i];
            j = i - 1;
            
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
        this->display();
    }
};

int main(){
    while(true){
        cout << "Choose sorting algorithm:" << endl;
        cout << "1. Selection Sort (int)" << endl;
        cout << "2. Selection Sort (float)" << endl;
        cout << "3. Insertion Sort (int)" << endl;
        cout << "4. Insertion Sort (float)" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                Temp<int> t1;
                cout << "Sorted array using Selection Sort is:" << endl;
                t1.selectionsort();
                break;
            }
            case 2: {
                Temp<float> t2;
                cout << "Sorted array using Selection Sort is:" << endl;
                t2.selectionsort();
                break;
            }
            case 3: {
                Temp<int> t3;
                cout << "Sorted array using Insertion Sort is:" << endl;
                t3.insertionsort();
                break;
            }
            case 4: {
                Temp<float> t4;
                cout << "Sorted array using Insertion Sort is:" << endl;
                t4.insertionsort();
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }
        cout<<"endl";
        cout << "Do you want to try again? (y/n): ";
        char c;
        cin >> c;

        if(c == 'n'){
            break;
        }
    }

    return 0;
}
