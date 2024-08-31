#include<iostream>
class Dq_demo
{
	int q[100];
	int front, rear;
	int size;
public:
	Dq_demo(int siz)
	{ front = -1;
	  rear = siz;
	  size = siz;
	  for(int i=0;i<siz;i++)
		q[i]=0;
	}
	void add_r(int x)
	{   //rear=(rear+1)%size;
	if((rear-1)!=front)
	{
	rear=(rear-1);
	q[rear] = x;
	//if(rear==0 && front ==-1)
	//	front = 0;
	}
	else
		cout<<"Queue is full";
	cout<<"rear "<<rear<<"\t"<<"front "<<front<<"\n";
	}
	void add_f(int x)
	{   //rear=(rear+1)%size;
	if((front+1)!=rear)
	{
	front=front+1;
	q[front] = x;
	}
	else
		cout<<"Queue is full";
	cout<<"rear "<<rear<<"\t"<<"front "<<front<<"\n";
	}

	int delete_f()
	{
	int x;
	x = -1;
	if(front==-1)
		cout<<"Queue is empty";
	else
	{       x = q[front];
		q[front]= -1;
		front=front-1;
	}
	cout<<"rear "<<rear<<"\t"<<"front "<<front<<"\n";
	return(x);
	}

	int delete_r()
	{
	int x;
	x = -1;
	if(rear==size)
		cout<<"Queue is empty";
	else
	{       x = q[rear];
		q[rear]= -1;
		rear=rear+1;
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
Dq_demo s1(si);
int ch,x;
char ans;
do
{
cout<<"MENU"<<"\n";
cout<<"1.ADD REAR"<<"\n";
cout<<"2.ADD FRONT"<<"\n";
cout<<"3.DELETE FRONT"<<"\n";
cout<<"4.DELETE REAR"<<"\n";
cout<<"5.DISPLAY"<<"\n";
cout<<"Enter your choice";
cin>>ch;
switch (ch)
{
case 1:
	cout<<"\n"<<"Enter number to add into queue at rear";
	cin>>x;
	s1.add_r(x);
	break;
case 2:
	cout<<"\n"<<"Enter number to add into queue at front";
	cin>>x;
	s1.add_f(x);
	break;

case 3:	x = s1.delete_f();
	if(x!=-1)
	cout<<"\n"<<"Element "<<x<<" deleted from queue from front";
	break;
case 4:	x = s1.delete_r();
	if(x!=-1)
	cout<<"\n"<<"Element "<<x<<" deleted from queue from rear";
	break;
case 5:
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
