#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main(){
    
    queue<int> q;
    stack<int> s;
    for(int i = 1; i <= 5; i++) 
    {   
        q.push(i);
        s.push(i);
    }
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
    int back = q.back();
    cout<<"back:"<<back<<endl;
    while(!q.empty()){
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
    return 0;
}
