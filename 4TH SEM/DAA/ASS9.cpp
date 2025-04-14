#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    int height;
    Node* left;
    Node* right;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        height = 1;
        left = right = nullptr;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int balanceFactor(Node* n) {
    return height(n->left) - height(n->right);
}

void updateHeight(Node* n) {
    n->height = 1 + max(height(n->left), height(n->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* balance(Node* n) {
    updateHeight(n);
    int bf = balanceFactor(n);
    if (bf > 1) {
        if (balanceFactor(n->left) < 0)
            n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (bf < -1) {
        if (balanceFactor(n->right) > 0)
            n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

Node* insert(Node* root, string k, string m) {
    if (!root) return new Node(k, m);
    if (k < root->keyword)
        root->left = insert(root->left, k, m);
    else if (k > root->keyword)
        root->right = insert(root->right, k, m);
    else
        root->meaning = m;
    return balance(root);
}

Node* findMin(Node* root) {
    return root->left ? findMin(root->left) : root;
}

Node* deleteNode(Node* root, string k) {
    if (!root) return nullptr;
    if (k < root->keyword)
        root->left = deleteNode(root->left, k);
    else if (k > root->keyword)
        root->right = deleteNode(root->right, k);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }
    return balance(root);
}

void update(Node* root, string k, string newMeaning) {
    if (!root) return;
    if (k < root->keyword)
        update(root->left, k, newMeaning);
    else if (k > root->keyword)
        update(root->right, k, newMeaning);
    else
        root->meaning = newMeaning;
}

void displayAsc(Node* root) {
    if (!root) return;
    displayAsc(root->left);
    cout << root->keyword << " : " << root->meaning << endl;
    displayAsc(root->right);
}

void displayDesc(Node* root) {
    if (!root) return;
    displayDesc(root->right);
    cout << root->keyword << " : " << root->meaning << endl;
    displayDesc(root->left);
}

int maxComparisons(Node* root) {
    return height(root);
}

bool search(Node* root, string k) {
    while (root) {
        if (k < root->keyword)
            root = root->left;
        else if (k > root->keyword)
            root = root->right;
        else
            return true;
    }
    return false;
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Add\n2. Delete\n3. Update\n4. Display Ascending\n5. Display Descending\n6. Max Comparisons\n7. Search\n8. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter keyword and meaning: ";
                cin >> key >> meaning;
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin >> meaning;
                update(root, key, meaning);
                break;
            case 4:
                displayAsc(root);
                break;
            case 5:
                displayDesc(root);
                break;
            case 6:
                cout << "Maximum comparisons (height): " << maxComparisons(root) << endl;
                break;
            case 7:
                cout << "Enter keyword to search: ";
                cin >> key;
                cout << (search(root, key) ? "Found" : "Not Found") << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}
