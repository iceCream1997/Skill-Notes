/*
输入一个链表，按链表值从尾到头的顺序返回一个ArrayList
 */

#include "head.h"
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int n):val(n),next(nullptr){}
};
/*
思路：该链表为单向链表，无论如何需要遍历一次链表，
先将节点值保存到栈中，再依次出栈返回结果。
*/
class solution{
public:
    vector<int> printListFromTailToHead(ListNode* head)
    {
        stack<int> temp;
        vector<int> result;
        while(head)
        {
            temp.push(head->val);
            head = head->next;
        }
        while(!temp.empty())
        {
            result.push_back(temp.top());
            temp.pop();
        }
        return result;
    }
};