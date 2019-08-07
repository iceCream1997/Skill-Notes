#include <vector>
#include <iostream>

int main(){
    
    //vector
    std::vector<int> vet1;
    for(int i = 1; i <= 6; i++)
        vet1.push_back(i);    //向尾部插入新的元素
    std::vector<int> vet2(5,1);      //初始大小为5，全是1
    std::vector<int>::iterator it1;
    for(it1 = vet1.begin();it1 != vet1.end(); it1++)
        std::cout<<*it1<<" ";
    std::cout<<std::endl;
    vet1.pop_back();            //删除尾元素
    vet1.erase(vet1.begin()+3); //删除第4个元素
    for(it1 = vet1.begin();it1 != vet1.end(); it1++)
        std::cout<<*it1<<" ";
    std::cout<<std::endl;
    vet1.insert(vet1.begin()+1,9); //在第2个元素前插入一个元素
    for(it1 = vet1.begin();it1 != vet1.end(); it1++)
        std::cout<<*it1<<" ";
    std::cout<<std::endl;

    return 0;
}