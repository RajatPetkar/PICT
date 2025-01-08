#include<iostream>
using namespace std;

struct Node{
    char data;
    Node* left;
    Node* right;
};

class BinaryTree{
    public:
        Node* root  = nullptr;


        Node* createNode(int data){
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        };

        void insert(int data){
            Node* newNode = createNode(data);
            if(root == nullptr){
                root = newNode;
            } else {
                if(root->left == nullptr) {
                    root->left = newNode;
                } else if(root->right == nullptr) {
                    root->right = newNode;
                }
                else {
                    insertRight(root,newNode);
                }
            }
        }

        void insertLeft(Node* node, Node* newNode) {
            if (node->left == nullptr) {
                node->left = newNode;
            } else {
                insertLeft(node->left, newNode);
            }
        }

        void insertRight(Node* node, Node* newNode) {
              if (node->right == nullptr) {
                    node->right = newNode;
              } else {
                    insertLeft(node->right, newNode);
              }
         }


        void preorder(Node* root){
            if (root == nullptr) return;
            cout << root->data << " -> ";
            preorder(root->left);
            preorder(root->right);
        }
        void Inorder(Node* root){
            if (root == nullptr) return;

            Inorder(root->left);
            cout << root->data << " -> ";
            Inorder(root->right);
        }
        void postorder(Node* root){
            if (root == nullptr) return;
            postorder(root->left);
            postorder(root->right);
            cout<< root->data << " -> ";

        }
        int count(Node* root){
        	int cnt = 0;
            Node* temp = root;
            while(temp!= nullptr ){
            	if(temp->left != nullptr){
            		temp = temp->left;
            	}
            	if(temp->right != nullptr){
            		temp = temp->right;
            	}
            	if(temp->left == nullptr && temp->right==nullptr){
            		cnt++;
            	}
            }
            return cnt;
        }
};

int main(){
    BinaryTree bt;
    int nodes;
	char data;
    cout<<"Enter how many nodes you want to insert :- ";
    cin>>nodes;

    for(int i=0;i<nodes;i++){
        cout<<"Enter data :- ";
        cin>>data;
        bt.insert(data);
    }

    bt.preorder(bt.root);
    cout<<endl;

    bt.Inorder(bt.root);
    cout<<endl;

    bt.postorder(bt.root);
    cout<<endl;

    cout<<bt.count(bt.root);

    return 0;
}
