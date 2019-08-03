#include <iostream>
#include <deque>

using namespace std;

int main(){
    deque<int> de1(3,5);
    deque<int> de2(2);

    de2.push_back(20);
    de2.push_front(30);
    deque<int>::iterator it2;
    for(it2 = de2.begin(); it2 != de2.end(); it2++)
        cout<<*it2<<" ";
    cout<<endl;

    de2.insert(de2.begin()+1,50);   //在第2个元素前插入一个50
    for(it2 = de2.begin(); it2 != de2.end(); it2++)
        cout<<*it2<<" ";
    cout<<endl;
    de2.erase(de2.begin()+3); //删除第4个元素

    for(it2 = de2.begin(); it2 != de2.end(); it2++)
        cout<<*it2<<" ";
    cout<<endl;

    return 0;
}
