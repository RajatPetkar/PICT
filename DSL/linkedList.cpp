#include <iostream>
using namespace std;

class Node
{
    float value;
    Node *next;

public:
    Node(float a)
    {
        value = a;
        next = NULL;
    }
    friend class List;
};

class List
{
    Node *head;

public:
    // CREATION OF LINKEDLIST
    List()
    {
        head = NULL;
    }
    // Traversal and Display
    void showList()
    {
        if (head)
        {
            cout << "list starts here\n";
            Node *nptr;
            nptr = head;
            while (nptr->next)
            {
                cout << nptr->value << endl;
                nptr = nptr->next;
            }
            cout << nptr->value;
            cout << "\nlist ends here\n";
        }
        else
        {
            cout << "null list\n";
        }
    }
    // appending of
    void appendNode(Node *newNode)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node *nptr;
            nptr = head;
            while (nptr->next)
            {
                nptr = nptr->next;
            }
            nptr->next = newNode;
        };
    }
    // inserting by  value directly
    void InsertNode(Node *newNode)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node *nptr;
            Node *prev;
            prev = head;
            nptr = head;
            while (nptr->value < newNode->value and nptr->next)
            {
                prev = nptr;
                nptr = nptr->next;
            }
            newNode->next = nptr;
            prev->next = newNode;
        };
    }
    // inserting at a position
    void InsertAt(Node *newNode, int pos)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node *nptr; 
            int count = 1;
            nptr = head;
            while (count < pos - 1 and nptr->next)
            {
                count++;
                nptr = nptr->next;
            }
            newNode->next = nptr->next;
            nptr->next = newNode;
        };
    }
    // inserting after
    void InsertAfter(Node *newNode, int num)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node *nptr;
            nptr = head;
            while (nptr->value != num and nptr->next)
            {
                nptr = nptr->next;
            }
            newNode->next = nptr->next;
            nptr->next = newNode;
        };
    }
    // inserting before
    void InsertBefore(Node *newNode, int num)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else if (head->value == num)
        {
            newNode->next = head->next;
            head = newNode;
        }
        else
        {
            Node *nptr;
            nptr = head;
            while (nptr->next->value != num and nptr->next)
            {
                nptr = nptr->next;
            }
            newNode->next = nptr->next;
            nptr->next = newNode;
        };
    }
}

;

int main()
{
    List l1;
    Node *n1 = new Node(5);
    Node *n2 = new Node(9);
    Node *n4 = new Node(55);
    Node *n3 = new Node(225);
    l1.appendNode(n1);
    // l1.appendNode(n2);
    // l1.showList();
    l1.appendNode(n3);
    // l1.showList();
    // l1.appendNode(n3);
    // l1.appendNode(n4);
    l1.InsertNode(n4);
    // l1.InsertNode(n2);
    // l1.InsertNode(n3);
    // l1.InsertNode(n4);
    l1.showList();
    // l1.InsertAfter(n2,5);
    l1.InsertBefore(n2, 5);
    l1.showList();
    return 0;
}
