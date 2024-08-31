#include<iostream>
#include<stdlib.h>
using namespace std;

class stack_demo
{
	int s[100];
	int top;
public:
	stack_demo()
	{ top = -1;
	  for(int i=0;i<100;i++)
		s[i]=0;
	}
	void push(int x)
	{
	if(top<99)
	{
		top=top+1;
		s[top] = x;
	}
	else
		cout<<"stack is full";
	}
	int pop()
	{
	int x;
	x = -1;
	if(top==-1)
		cout<<"stack is empty";
	else
	{
		x = s[top];
		s[top]= -1;
		top = top-1;
	}
	return(x);
	}
	int top_ele()
	{
	return(s[top]);
	}
	int empty()
	{
		if(top>=0)
			return(0);
		else
			return(1);
	}
	void display()
	{
	for(int i=top;i>-1;i--)
		cout<<s[i]<<"\n";
	}
};

class expr
{

public:

void eval(char str[])
{
int le;
stack_demo s1;
int i,k,opr,opl,ans;
i=0;
k=0;
while(str[i]!= '\0') // str[i]!='\0'
{
if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/')
{
opr =s1.pop();
opl = s1.pop();

if(str[i]==’+’)
	ans = opl+opr;
if(str[i]==’-’)
	ans = opl-opr;
if(str[i]==’*’)
	ans = opl*opr;
if(str[i]==’/’)
	ans = opl/opr;

s1.push(ans);
}
else
{
       int x;
    cout<<" Enter value of “ <<str[i];
    cin>>x;
    s1.push(x);}
}
i++;
}
cout<< "Result is"<<s1.pop();
}

};     //class end

main()
{
int si;
char ex[50],ans;
cout<<"hello"<<"\n";
//do
//{
cout<<"Enter the postfix expression";
cin>>ex;
//stack_demo s1;
expr e1;
e1.eval(ex);

//cout<<"Do you want to continue (y/n)"<<"\n";
//cin>>ans;
//}while(ans='y'||ans=='Y');
//if(ans=='n'||ans=='N')
//
}
