#include<iostream>
#include<queue>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};


void insert(Node* root, char data) {
    if (root == nullptr) return;


    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();


        if (current->left == nullptr) {
            current->left = new Node(data);
            return;
        } else {
            q.push(current->left);
        }


        if (current->right == nullptr) {
            current->right = new Node(data);
            return;
        } else {
            q.push(current->right);
        }
    }
}


void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " -> ";
    preorder(root->left);
    preorder(root->right);
}


void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " -> ";
    inorder(root->right);
}


void postorder(Node* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " -> ";
}


void count(Node* root,int &leaf , int &parent) {
    if (root == nullptr) return ;
    if (root->left == nullptr && root->right == nullptr)
    	leaf++;
    else
    	parent++;

    count(root->left,leaf,parent);
    count(root->right,leaf,parent);
}


// int countInternal(Node* root) {
//     if (root == nullptr) return 0;
//     if (root->left != nullptr || root->right != nullptr) {
//         return 1 + countInternal(root->left) + countInternal(root->right);
//     }
//     return 0;
// }

int findHeight(Node* root){
	if(root==nullptr){
		return -1;
	}
	int leftHeight = findHeight(root->left);
	int rightHeight = findHeight(root->right);
	return max(leftHeight,rightHeight) + 1;
}

Node* copy(Node* root){
    if(root==nullptr){
        return nullptr;
    }
    Node* temp = new Node(root->data);
    if(root->left !=nullptr){
        temp->left = root->left;
    }
    if(root->right != nullptr){
        temp->right = root->right;
    }
    copy(root->left);
    copy(root->right);

    return temp;
}

void del(Node* root) {
    if (root == nullptr) return;
    if(root->left){
        root->left = nullptr;
    }else{
        root->right = nullptr;
    }
    del(root->left);
    del(root->right);
    delete root;
}

void Swap(Node* root){
	if(root==nullptr){
		return;
	}
	Swap(root->left);
	Swap(root->right);
                                           
	Node* temp = root->left;
	root->left = root->right;
	root->right = temp;
}

int main() {
    Node* root = nullptr;
    int leaf = 0, parent = 0;
    int nodes;
    char data;

    cout << "Enter how many nodes you want to insert: ";
    cin >> nodes;

    for (int i = 0; i < nodes; i++) {
        cout << "Enter data: ";
        cin >> data;

        if (root == nullptr) {
            root = new Node(data);
        } else {
            insert(root, data);
        }
    }


    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    cout<<"\nAfter swapping :- \n";
    Swap(root);
    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    count(root,leaf,parent);
    cout << "Number of leaf nodes: " <<leaf<<endl;
    cout << "Number of internal nodes: " << parent<<endl;
    cout << "Height of tree : " << findHeight(root) << endl;

    Node* root2 = copy(root);
    inorder(root2);
    cout<<endl;
    del(root2);
    inorder(root2);

    return 0;
}
