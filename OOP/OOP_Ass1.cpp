#include<iostream>
using namespace std;

class Complexo{
    private:
    int real,imag;
    public:
    Complexo(){
        real=0;
        imag=0;
    }
    Complexo operator* (Complexo t){
        Complexo temp;
        temp.real= real*t.real - imag*t.imag;
        temp.imag= t.real*imag + real*t.imag;
        return temp;
    }
    Complexo operator+ (Complexo t){
        Complexo temp;
        temp.real=real + t.real;
        temp.imag=imag + t.imag;
        return temp;
    };
    Complexo operator- (Complexo t){
        Complexo temp;
        temp.real=real - t.real;
        temp.imag=imag - t.imag;
        return temp;
    };
    friend void operator>>(istream&in, Complexo &c);
    friend void operator<<(ostream&out, Complexo &c);
};
void operator>>(istream &in, Complexo &c){
    cout<<"enter real part:";
    in>>c.real;
    cout<<"enter imaginary part:";
    in>>c.imag;
}
void operator<<(ostream &out, Complexo &c){
    out<<c.real;
    out<<"+"<<c.imag<<"i;"<<endl;
}

int main(){
    Complexo c1,c2,c3;
    cout<<"enter the first complex number\n";
    cin>>c1;
    cout<<"complex object is\n";
    cout<<c1;
    cout<<"enter the second complex number\n";
    cin>>c2;
    cout<<"complex object is\n";
    cout<<c2;
    cout<<"There addition is:\n";
    c3=c1+c2;
    cout<<c3;
    cout<<"There subtraction is:\n";
    c3=c1-c2;
    cout<<c3;
    cout<<"There multiplication is:\n";
    c3=c1*c2;
    cout<<c3;
    
    return 0;
}