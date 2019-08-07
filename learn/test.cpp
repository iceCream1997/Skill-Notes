#include <bits/stdc++.h>

using namespace std;

class base{
public:
    void fun(){cout<<"hello"<<endl;}
};

class derived:public base{
public:
    void fun(){cout<<"world"<<endl;}
    void fun2(){cout<<"error"<<endl;}
};

int main(){
    base* b1 = new base();
    base* b2 = new derived();
    derived* d1 = static_cast<derived*>(b1);
    b1->fun();
    d1->fun2();
    return 0;
}