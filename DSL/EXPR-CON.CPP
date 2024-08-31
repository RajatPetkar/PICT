#include<iostream>
#include<stdlib.h>
using namespace std;

class stack_demo
{
	char s[100];
	int top;
public:
	stack_demo()
	{ top = -1;
	  for(int i=0;i<100;i++)
		s[i]=0;
	}
	void push(char x)
	{
	if(top<99)
	{
		top=top+1;
		s[top] = x;
	}
	else
		cout<<"stack is full";
	}
	char pop()
	{
	char x;
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
	char top_ele()
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

int priority(char x)
{
  if(x=='+'|| x=='-')
	return(1);
  if(x=='*' || x=='/')
	return(2);
  return(0);
}

/*void eval(char str[])
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
s1.push(str[i]);
}
}
}*/



void convert(char str[])
{
int le;
char result[30];
stack_demo s1;
int i,j,k;
i=0;
j=0;
k=0;
for(j=0;str[j]!='\0';j++)
	//cout<<str[j];
while(i<=j) // str[i]!='\0'
{
//cout<<str[i];
if( str[i] == '(')
	s1.push(str[i]);
else
{       int r1;
	r1 = str[i];
	cout<<" r1 "<<r1;
	if(r1>=96&& r1<=123)
	{	result[k] = str[i];
		cout<<"result k "<<result[k]<<'\n';
		k=k+1;
	}
	else
	{
		if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/')
		{
			int pri;
			pri = priority(str[i]);
			cout<<"operator "<<str[i]<<" " <<pri<<'\n';
			if(s1.empty())
			{
				s1.push(str[i]);
			}
			else
			{
			while(priority(s1.top_ele())>=pri && !s1.empty())
			{	result[k] = s1.pop();
				k++;
			}
			s1.push(str[i]);
			}
		}
		else
		{
			if(str[i]==')')
			{
			while(s1.top_ele()!='(')
			{
				result[k] = s1.pop();
				k++;
			}
			s1.pop();
			}
		}
	}
}   //else end
i++;
}        //while end
while(!s1.empty())
{
	result[k] = s1.pop();
	k++;
}
result[k] = '\0';
for(i=0;i<k;i++)
	cout<<result[i];

//eval(result);


}//function end



};     //class end

main()
{
int si;
char ex[50],ans;
cout<<"hello"<<"\n";
//do
//{
cout<<"Enter the infix expression";
cin>>ex;
stack_demo s1;
expr e1;
e1.convert(ex);



//cout<<"Do you want to continue (y/n)"<<"\n";
//cin>>ans;
//}while(ans='y'||ans=='Y');
//if(ans=='n'||ans=='N')
//
}
