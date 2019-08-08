#include "head.h"

using namespace std;

class A{

};

class B:public A{

};

void test()
{

}

int main()
{
  chrono::milliseconds dura(1000);
  this_thread::sleep_for(dura);
}