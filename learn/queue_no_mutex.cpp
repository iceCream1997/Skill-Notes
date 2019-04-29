#include <bits/stdc++.h>


struct Node{
    int data;
   Node* next;
};

bool CAS(Node *accum, Node *dest, Node* newval)
{
  if (accum == dest) {
      accum = newval;
      return true;
  } 
      return false;
}

class queue{
public:
    queue(){}
    void push(int x){
        q = new Node();
        q->data = x;
        q->next = NULL;
        p = tail;
        oldp = p;
    do{
        while(p->next != NULL)
            p = p->next;
    }while( CAS(p->next,NULL,q) != true);
    CAS(tail,oldp,q);
    }
    int pop(){
        do{
            p = head;
            if(p->next == NULL)
                return -1;
        }while(CAS(head,p,p->next));

        return p->next->data;
    }

    ~queue(){}
private:
    Node* head;
    Node* tail;
    Node* q;
    Node* p;
    Node* oldp;
};

queue qu;

void f1(){
    for(int i = 0; i < 10; i++)
    {
        qu.push(i);
        std::cout<<"t1 push:"<<i<<std::endl;
    }
}

void f2(){
    for(int i = 0; i < 10; i++)
        {
            qu.push(i);
            std::cout<<"t2 push:"<<i<<std::endl;
        }
}

void f3(){
    for(int i = 0; i < 5; i++){
        qu.push(i);
        std::cout<<"t3 push:"<<i<<std::endl;
    }
}

void f4(){
    int result;
    while( (result = qu.pop()) != -1){
        std::cout<<"t4 pop:"<<result<<std::endl;
    }
    
       
    
}
int main(){
    std::thread t1(f1);
    std::thread t2(f2);
    std::thread t3(f3);
    std::thread t4(f4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}