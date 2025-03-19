#include<iostream>
#include<string.h>
using namespace std;

class SLL
{
public:
    int key;
    char val[10];
    SLL *next;
}HT[6];

class OpenHash
{
public:
    SLL *node;
    OpenHash()
    {
        for(int i=0; i<6; i++)
        {
            HT[i].key = 0;
            strcpy(HT[i].val,"---");
            HT[i].next = NULL;
        }
    }
    void insert_KeyVal();
    void show_Table();
    void find_KeyVal();
    void delete_KeyVal();
};

void OpenHash :: insert_KeyVal()
{
    int i, cnt, index;
    SLL *Newnode, *temp;

    cout<<"\n\t How many Key-Value Pairs to Insert: ";
    cin>>cnt;

    for(i=0; i<cnt; i++)
    {
        Newnode = new SLL;
        
        cout<<"\n\t Enter Key : ";
        cin>>Newnode->key;
        cout<<"\n\t Enter Val : ";
        cin>>Newnode->val;
        Newnode->next = NULL;


        index = Newnode->key % 6;

        if(HT[index].next == NULL)
        {
            HT[index].next = Newnode;
        }
        else
        {
            temp = HT[index].next;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = Newnode;
        }

    }
}

void OpenHash :: show_Table()
{
    int i;
    SLL *temp;

    cout<<"\n\n\t Index Key->Value.....";
    for(i=0; i<6; i++)
    {
        cout<<"\n\n\t"<<i<<"--->";
        temp = HT[i].next;
        while(temp)
        {
            cout<<temp->key<<"--"<<temp->val<<"---->";
            temp = temp->next;
        }
    }
}


int main()
{
    OpenHash H1;

    H1.insert_KeyVal();

    H1.show_Table();

    return 0;
}
