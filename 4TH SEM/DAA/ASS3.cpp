#include<iostream>
#include<stack>
using namespace std;

class TBT{
public:
    int data;
    TBT *left;
    TBT *right;
    bool lthread;
    bool rthread;
}*root;

class ThreadBT{
public:
    void insert(TBT *root, TBT *newNode) {
        int flag = 0;
        while (flag != 1) {
            if (newNode->data < root->data) {
                if (root->left == NULL || root->lthread == true) {
                    newNode->left = root->left;
                    newNode->lthread = root->lthread;
                    root->left = newNode;
                    root->lthread = false;
                    newNode->right = root;
                    newNode->rthread = true;

                    flag = 1;
                }
                else {
                    root = root->left;
                }
            }
            else {
                if (root->right == NULL || root->rthread == true) {
                    newNode->right = root->right;
                    newNode->rthread = root->rthread;
                    root->right = newNode;
                    root->rthread = false;
                    newNode->left = root;
                    newNode->lthread = true;

                    flag = 1;
                }
                else {
                    root = root->right;
                }
            }
        }
    }

    TBT* leftMost(TBT *node) {
        if (node == NULL) {
            return NULL;
        }
        while (node->left != NULL && node->lthread == false) {
            node = node->left;
        }
        return node;
    }

    void threaded_inorder(TBT *root) {
        TBT *Curr = leftMost(root);
        
        while (Curr != NULL) {
            cout << Curr->data << " ";
            if (Curr->rthread == true) {
                Curr = Curr->right;
            }
            else {
                Curr = leftMost(Curr->right);
            }
        }
    }

void threaded_preorder(TBT *root) {
    TBT *Curr = root;

    while (Curr != NULL) {
        cout << Curr->data << " ";

        if (Curr->lthread == false && Curr!=nullptr) {
            Curr = Curr->left;
        }
        else{
            if (Curr->rthread == true) {
                Curr = Curr->right;
            }else{
                break;
            }
        } 
    }
}

void preorder(TBT* root) {
    if (root == nullptr) return;
    
    stack<TBT*> s;
    s.push(root);
    
    while (!s.empty()) {
        TBT* current = s.top();
        s.pop();
        cout << current->data << " -> ";
        
        if (current->right && current->rthread == false) 
            s.push(current->right);
        if (current->left && current->lthread == false) 
            s.push(current->left);
    }
}

    void deleteTree(TBT* node) {
        if (node == NULL) {
            return;
        }
        if (node->lthread == false) {
            deleteTree(node->left);
        }
        if (node->rthread == false) {
            deleteTree(node->right);
        }
        delete node;
    }
};

int main() {
    TBT* newNode;
    int i, nodes;

    root = nullptr;
    ThreadBT T1;

    cout << "How many nodes to add in TBT? ";
    cin >> nodes;

    if (nodes == 0) {
        cout << "No nodes to add. Exiting...\n";
        return 0;
    }

    for (i = 0; i < nodes; i++) {
        newNode = new TBT;
        cout << "Enter data for TBT: ";
        cin >> newNode->data;

        newNode->left = NULL;
        newNode->right = NULL;
        newNode->lthread = false;
        newNode->rthread = false;

        if (root == nullptr) {
            root = newNode;
        }
        else {
            T1.insert(root, newNode);
        }
    }

    cout << "In-order traversal of the threaded binary tree:\n";
    T1.threaded_inorder(root);
    cout<<endl;
    T1.preorder(root);

    T1.deleteTree(root);

    return 0;
}
