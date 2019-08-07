#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct Node{
    int x, y;
    Node( int a= 0, int b= 0 ):
        x(a), y(b) {}
};
struct cmp{
    bool operator() ( Node a, Node b ){
        if( a.x== b.x ) return a.y> b.y;
         
        return a.x> b.x; }
};

int main(){

    priority_queue<int> big;  //建立大根堆
    for(int i = 0; i < 5; i++)
        big.push( rand()%10);
    while(!big.empty()){
        cout<<big.top()<<" ";
        big.pop();
    }
    cout<<endl;

    priority_queue<int,vector<int>,greater<int> > small;
    for(int i = 0; i < 5; i++)
        small.push( rand()%5+1);
    while(!small.empty()){
        cout<<small.top()<<" ";
        small.pop();
    }
    cout<<endl;

    priority_queue<Node, vector<Node>, cmp> q;     
    for( int i= 0; i< 5; ++i )
        q.push( Node( rand()%100, rand()%50 ) );
    while( !q.empty() ){
        cout << q.top().x << ' ' << q.top().y << endl;
        q.pop();
    }

    return 0;
}