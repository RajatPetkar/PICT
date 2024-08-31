#include<iostream>
using namespace std;
class Cqu;
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
	friend class Cqu;
};
class Cqu
{
	node *front, *rear;
public:
       Cqu()
       {   front= NULL;
	   rear = NULL;
       }
       void add(int x)
       {
	if(rear==NULL)
	{       rear = new node(x);
		rear->next = rear;
		front = rear;
	}
	else
	{	node *temp;
		temp = new node(x);
		rear->next = temp;
		temp->next = front;
		rear = temp;
	}
	cout<<"\n"<<"front "<<front->data<<"rear "<<rear->data<<"\t";
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
		cout<<"\n"<<x<<"is deleted"<< "was presented at location"<<front;
		if(front!=rear)
		{
			front=front->next;
			rear->next = front;
			cout<<"\n"<<"front "<<front->data<<"rear "<<rear->data<<"\t";
		}
		else
		{
			front=NULL;
			rear = NULL;
			cout<<"\n"<<"front "<<"NULL"<<"rear "<<"NULL"<<"\t";
		}
		temp->next = NULL;
		free(temp);

		return(x);
       }
	void display()
	{
	if(front==NULL)
		cout<<"Queue is empty ";
	else
	{
		node *temp;
		temp = front;
		if( front!=rear)
		{
		while(temp!=rear)
		{
			cout<<"\n"<<temp->data<<"\t"<<temp<<"\n";
			temp = temp->next;
		}
		cout<<"\n"<<temp->data<<"\t"<<temp<<"\n";
		}
		else
		{
			cout<<"\n"<<temp->data<<"\t"<<temp<<"\n";
			temp = temp->next;
		}
	}
	}
};
main()
{
int si;
cout<<"hello"<<"\n";
Cqu s1;
int ch,x;
char ans;
do
{
cout<<"MENU"<<"\n";
cout<<"1.INSERT REAR "<<"\n";
cout<<"2.DELETE FRONT "<<"\n";
cout<<"3.DISPLAY "<<"\n";
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
}
