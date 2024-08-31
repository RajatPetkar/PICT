#include <iostream>
using namespace std;

class Node
{

public:
    int value;
    Node *next;
    Node(float a)
    {
        value = a;
        next = NULL;
    }
    friend class List;
};

class List
{

public:
    Node *head;
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
            Node *nptr;
            nptr = head;
            while (nptr->next)
            {
                cout << nptr->value << endl;
                nptr = nptr->next;
            }
            cout << nptr->value;
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
        if (head == NULL || newNode->value < head->value)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            Node *nptr;
            Node *prev;
            prev = head;
            nptr = head;
            while (nptr->value < newNode->value && nptr->next)
            {
                prev = nptr;
                nptr = nptr->next;
            }
            newNode->next = nptr;
            prev->next = newNode;
        }
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
    friend void intersection(List l1, List l2);
    friend void uni(List l1, List l2);
    friend bool valueInList(int num);
};
bool valueInList(List l1, int num)
{
    Node *head = l1.head;
    while ((head))
    {
        if (head->value == num)
        {
            return true;
            break;
        }
        head = head->next;
    }
    return false;
};

void intersection(List l1, List l2)
{
    List l3;
    Node *t1 = l1.head;
    Node *t2 = l2.head;

    while (t1)
    {
        t2 = l2.head;
        while (t2)
        {
            if (t1->value == t2->value)
            {
                Node *n1 = new Node(t1->value);
                l3.appendNode(n1);
                break;
            }
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    l3.showList();
};

void uni(List l1, List l2)
{
    List unilist;
    Node *t1 = l1.head;
    Node *t2 = l2.head;

    while (t1)
    {
        Node *n1 = new Node(t1->value);
        unilist.appendNode(n1);
        t1 = t1->next;
    }
    while (t2)
    {
        if ((valueInList(unilist, t2->value) == false))
        {

            Node *n2 = new Node(t2->value);
            unilist.appendNode(n2);
        }
        t2 = t2->next;
    }
    unilist.showList();
};
int main()
{
    List l1, but, van, buv, bnv;
    int stud;
    cout << "The number of students is:\n";
    cin >> stud;
    int i = 0;
    while (i < stud)
    {
        int roll = 0;
        cout << "Enter roll Number: \n";
        cin >> roll;
        if (valueInList(l1, roll) || (roll < 0))
        {
            cout << "negative values/repeated values not allowed";
            continue;
        }
        Node *node1 = new Node(roll);
        l1.appendNode(node1);
        i++;
    }

    int vn;
    cout << "The number of students liking vanilla is:\n";
    cin >> vn;
    int j = 0;
    while (j < vn)
    {
        int roll = 0;
        cout << "Enter roll Number of Vanilla lover: \n";
        cin >> roll;
        if (valueInList(l1, roll))
        {
            Node *node1 = new Node(roll);
            van.appendNode(node1);
            j++;
        }
        else
        {
            cout << "student should be of same class\n";
        }
    }

    int bs;
    cout << "The number of students liking butterscotch is:\n";
    cin >> bs;
    int k = 0;
    while (k < bs)
    {
        int roll = 0;
        cout << "Enter roll Number of butterscotch lover: \n";
        cin >> roll;

        if (valueInList(l1, roll))
        {
            Node *node1 = new Node(roll);
            but.appendNode(node1);
            k++;
        }
        else
        {
            cout << "student should be of same class\n";
        }
    }
    cout << "Rolls of students liking icecream: \n";
    uni(van, but);
    cout << "\nRolls of students liking both vanilla and butterscotcch flavours: \n";
    intersection(van, but);
    return 0;
}
