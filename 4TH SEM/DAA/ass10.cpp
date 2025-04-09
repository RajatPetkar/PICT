#include <iostream>
#include <queue>
using namespace std;

class Node {
    int val;
    Node* left = nullptr;
    Node* right = nullptr;

public:
    friend class Heap;
};

class Heap {
    Node* ROOT = nullptr;
    int numNodes = 0;
    bool isMaxHeap;

public:
    Heap(bool isMaxHeap = true) : isMaxHeap(isMaxHeap) {}

    void insert(int keys[], int n) {
        numNodes = n;

        Node* newNode = new Node();
        newNode->val = keys[0];
        ROOT = newNode;

        int i = 0;
        queue<Node*> q;
        q.push(ROOT);

        while (i < n - 1) {
            Node* poppedNode = q.front();
            q.pop();

            Node* leftNode = new Node();
            leftNode->val = keys[++i];
            poppedNode->left = leftNode;
            q.push(poppedNode->left);

            if (i < n - 1) {
                Node* rightNode = new Node();
                rightNode->val = keys[++i];
                poppedNode->right = rightNode;
                q.push(poppedNode->right);
            }
        }
    }

    void breadthFirst() {
        queue<Node*> q;
        q.push(ROOT);
        while (!q.empty()) {
            Node* poppedNode = q.front();
            cout << poppedNode->val << " ";
            q.pop();
            if (poppedNode->left != nullptr) {
                q.push(poppedNode->left);
            }
            if (poppedNode->right != nullptr) {
                q.push(poppedNode->right);
            }
        }
        cout << "\n";
    }

    Node* heapify(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        node->left = heapify(node->left);
        node->right = heapify(node->right);

        if (isMaxHeap) {
            if (node->left != nullptr && node->left->val > node->val) {
                int temp = node->left->val;
                node->left->val = node->val;
                node->val = temp;
            }
            if (node->right != nullptr && node->right->val > node->val) {
                int temp = node->right->val;
                node->right->val = node->val;
                node->val = temp;
            }
        } else { // Min Heap
            if (node->left != nullptr && node->left->val < node->val) {
                int temp = node->left->val;
                node->left->val = node->val;
                node->val = temp;
            }
            if (node->right != nullptr && node->right->val < node->val) {
                int temp = node->right->val;
                node->right->val = node->val;
                node->val = temp;
            }
        }
        return node;
    }

    void sort() {
        for (int i = 0; i < numNodes; i++) {
            heapify(ROOT);

            Node* lastNode = getLastNodeValue();
            int temp = ROOT->val;
            ROOT->val = lastNode->val;
            lastNode->val = temp;
            cout << lastNode->val << " ";
            deleteNode(ROOT, lastNode->val);
        }

        cout << "\n";
    }

    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->val == val) {
            delete node;
            return nullptr;
        }
        node->left = deleteNode(node->left, val);
        node->right = deleteNode(node->right, val);
        return node;
    }

    Node* getLastNodeValue() {
        queue<Node*> q;
        q.push(ROOT);
        Node* poppedNode = nullptr;
        while (!q.empty()) {
            poppedNode = q.front();
            q.pop();
            if (poppedNode->left != nullptr) {
                q.push(poppedNode->left);
            }
            if (poppedNode->right != nullptr) {
                q.push(poppedNode->right);
            }
        }
        return poppedNode;
    }
};

int main() {
    int keys[7] = {87, 5, 34, 99, 44, 12, 68};

   
    Heap maxHeap(true); 
    maxHeap.insert(keys, 7);
    cout << "Max Heap Sorted: ";
    maxHeap.sort();

    Heap minHeap(false);
    minHeap.insert(keys, 7);
    cout << "Min Heap Sorted: ";
    minHeap.sort();

    return 0;
}
