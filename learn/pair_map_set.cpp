#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(){
    map<int,int> m;
    set<pair<int,int> > s;
    for(int i = 1; i <= 3; i++)
        m[i] = rand()%20+1;
    
    for(map<int,int>::iterator it = m.begin(); it != m.end(); it++)
        cout<<it->first<<" "<<it->second<<endl;
    cout<<endl;
    m.insert(make_pair(12,30));
    for(map<int,int>::iterator it = m.begin(); it != m.end(); it++)
        cout<<it->first<<" "<<it->second<<endl;
    cout<<endl;

    for(int i = 1; i <= 3; i++)
    {
        s.insert(pair<int,int>(i,rand()%20));
    }
    s.insert(pair<int,int>(2,30));
    set<pair<int,int> >::iterator it;
    for(it = s.begin(); it != s.end(); it++)
         cout<<it->first<<" "<<it->second<<endl;
    return 0;
}