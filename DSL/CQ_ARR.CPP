#include<iostream>
using namespace std;
class q_demo
{
	int q[100];
	int front, rear;
	int size;
public:
	q_demo(int siz)
	{ front = -1;
	  rear = -1;
	  size = siz;
	  for(int i=0;i<siz;i++)
		q[i]=0;
	}
	void add(int x)
	{   //rear=(rear+1)%size;
	if((rear+1)%size!=front)
	{
	rear=(rear+1)%size;
	q[rear] = x;
	if(rear==0 && front ==-1)
		front = 0;
	}
	else
		cout<<"Queue is full";
	cout<<"rear "<<rear<<"\t"<<"front "<<front<<"\n";
	}
	int deletee()
	{
	int x;
	x = -1;
	if(front==-1)
		cout<<"Queue is empty";
	else
	{       x = q[front];
		q[front]= -1;
		if(front==rear)
		{
			front=-1;
			rear = -1;
		}
		else
		{	front = (front+1)%size;
			cout<<"front"<<front;             }
	}
	cout<<"rear "<<rear<<"\t"<<"front "<<front<<"\n";
	return(x);
	}
	void display()
	{
	cout<<"rear "<<rear<<"\t"<<"front "<<front<<"\n";
	//for(int i=rear+1;i!=rear;i=(i+1)%size)  //(i+1)%size)
	for(int i=0;i<size;i++)  //(i+1)%size)
		cout<<"data "<<q[i]<<"\n";

	}
}
main()
{
int si;
cout<<"hello"<<"\n";
cout<<"Enter the size of Queue";
cin>>si;
q_demo s1(si);
int ch,x;
char ans;
do
{
cout<<"MENU"<<"\n";
cout<<"1.ADD"<<"\n";
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
	x = s1.deletee();
	if(x!=-1)
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
/*s1.push(10);
s1.push(20);
s1.display();
s1.pop();
s1.display();*/
}while(ans='y'||ans=='Y');
}
