#include<iostream>
#include<queue>
#include<stack>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void insert(Node* &root, int data) {
    if (root == nullptr) {
        root = new Node(data);
        return;
    }
    if (data <= root->data) {
        insert(root->left, data);
    } else {
        insert(root->right, data);
    }
}


void preorder(Node* root) {
    if (root == nullptr) return;
    
    stack<Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " -> ";
        
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

void inorder(Node* root) {
    stack<Node*> s;
    Node* current = root;
    
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        
        current = s.top();
        s.pop();
        cout << current->data << " -> ";
        
        current = current->right;
    }
}



void postorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " -> ";
        s2.pop();
    }
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
    del(root->left);
    del(root->right);
    root->left = nullptr;
    root->right = nullptr;
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

void minMAX(Node* root){
    Node* temp = root;
    int min = 0;
    int max = 0;

    while(temp->left!=nullptr){
        temp = temp->left;
    }
    min = temp->data;

    temp = root;
    while(temp->right!=nullptr){
        temp= temp->right;
    }
    max = temp->data;

    cout<<"Min value is "<<min <<" && " <<"max value is "<<max;
}

void search(Node* root,int s){
    Node* temp = root;
    while(temp!=nullptr){
        if(s < temp->data){
            temp= temp->left;
        }
        if(s==temp->data){
            cout<<"element found!";
            break;
        }
        if(s>temp->data){
            temp= temp->right;
        }
    }
    if(temp==nullptr){
        cout<<"not found";
    }
}

 void delNode(Node *root, int element) {
    if (root == nullptr) {
        return; 
    }
    Node* parent = nullptr;
    Node* temp = root;

    while (temp != nullptr && temp->data != element) {
        parent = temp;

        if (element < temp->data) {
            if (temp->left != nullptr) {
                temp = temp->left;
            } else {
                return; 
            }
        } else {
            if (temp->right != nullptr) {
                temp = temp->right;
            } else {
                return; 
            }
        }
    }

    if (temp->left == nullptr && temp->right == nullptr) {
        
        if (parent == nullptr) {
            delete temp;  
            root = nullptr; 
        } else {
            if (parent->left == temp) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete temp;
        }
    }
    else if(temp->left==NULL || temp->right==NULL){
        Node* child = (temp->left != nullptr) ? temp->left : temp->right;
        if(parent == nullptr){
            root = child;
        }else{
            if (parent->left == temp) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
        delete temp;
    }
}

int main() {
    Node* root = nullptr;
    int leaf = 0, parent = 0;
    int nodes;
    int data;

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
    cout << endl<<endl;

    minMAX(root);
    cout<<endl;

    int ch;
    cout<<"enter element to search :";
    cin>>ch;
    search(root,ch);
    delNode(root,ch);
    preorder(root);
    // cout<<"\nAfter swapping :- \n";
    // Swap(root);
    // cout << "Preorder: ";
    // preorder(root);
    // cout << endl;

    // cout << "Inorder: ";
    // inorder(root);
    // cout << endl;
    // cout << "Postorder: ";
    // postorder(root);
    // cout << endl;
    // count(root,leaf,parent);
    // cout << "Number of leaf nodes: " <<leaf<<endl;
    // cout << "Number of internal nodes: " << parent<<endl;
    // cout << "Height of tree : " << findHeight(root) << endl;

    // minMAX(root);
    return 0;

}

/*
Enter how many nodes you want to insert: 5
Enter data: 4
Enter data: 5
Enter data: 6
Enter data: 7
Enter data: 8
Preorder: 4 -> 5 -> 6 -> 7 -> 8 -> 
Inorder: 4 -> 5 -> 6 -> 7 -> 8 -> 
Postorder: 8 -> 7 -> 6 -> 5 -> 4 -> 

Min value is 4 && max value is 8
enter element to search :4
*/
