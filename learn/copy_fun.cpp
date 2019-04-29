#include <iostream>
#include <cstdio>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

class test{
public:
    test();
    test(const test &t);
    ~test();
private:
    int num;
    char* name;
};

test::test(){
    num = 0;
    name = new char(20);
    cout<<"gouzao:"<<(long)name<<endl;
}

test::test(const test &t){
    num = t.num;
    name = new char(20);
    memcpy(name,t.name,strlen(t.name));
}

test::~test(){
    cout<<"xigou test:"<<(long)name<<endl;
    delete[] name;
    name = NULL;
}

int main(){
    test t1;
    test t2(t1);
    return 0;
}