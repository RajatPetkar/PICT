#include<iostream>
using namespace std;
class qu;
class node
{
	int data;
	node *next;
public:
	node(int x)
	{
		data = x;
		next = NULL;
	}
	friend class qu;
};
class qu
{
	node *front, *rear;
public:
       qu()
       {   front= NULL;
	   rear = NULL;
       }
       void add(int x)
       {
	if(rear==NULL)
	{       rear = new node(x);
		front = rear;
	}
	else
	{	node *temp;
		temp = new node(x);
		rear->next = temp;
		rear = temp;
	}
       }
       int delet()
       {        int x;
		node *temp;
		temp = front;
		if(front==NULL)
		{	cout<<"queue is empty";
			return 0;
		}
		x = front->data;
		cout<< x<<"is deleted"<< "was presented at location"<<front;
		front=front->next;
		free(temp);
		if(front==NULL)
			rear = NULL;

		return(x);
       }
	void display()
	{
	node *temp;
	temp = front;
	while(temp!=NULL)
	{
		cout<<temp->data<<"\t"<<temp<<"\n";
		temp = temp->next;
	}
	}
};
main()
{
int si;
cout<<"hello"<<"\n";
qu s1;
int ch,x;
char ans;
do
{
cout<<"MENU"<<"\n";
cout<<"1.INSERT START "<<"\n";
cout<<"2.DELETE"<<"\n";
cout<<"3.DISPLAY"<<"\n";
cout<<"Enter your choice";
cin>>ch;
switch (ch)
{
case 1:
	cout<<"\n"<<"Enter number to add into queue";
	cin>>x;
	s1.add(x);
	break;
case 2:
	x = s1.delet();
	if(x!=0)
	cout<<"\n"<<"Element "<<x<<" deleted from queue";
	break;
case 3:
	s1.display();
	break;
default:
	return(0);
}
cout<<"\n"<<"Do you want to continue (y/n)"<<"\n";
cin>>ans;
}while(ans='y'||ans=='Y');
return(0);
}
