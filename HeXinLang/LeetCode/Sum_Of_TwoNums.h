/*
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，
并且它们的每个节点只能存储 一位 数字。
如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
示例：
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
*/
#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class solution
{
public:
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode* pre = new ListNode(0);
        ListNode* p = pre;
        int car = 0;
        while(l1 || l2)
        {
            if(l1 && l2)
            {
                p->next = new ListNode(l1->val + l2->val + car);
                p = p->next;
                l1 = l1->next;
                l2 = l2->next;
                if(p->val >= 10)
                {
                    p->val -= 10;
                    car = 1;
                }
                else
                {
                    car = 0;
                }
                
            }
            else if(l1)
            {
                p->next = new ListNode(l1->val + car);
                p = p->next;
                l1 = l1->next;
                if(p->val >= 10)
                {
                    p->val -= 10;
                    car = 1;
                }
                else
                {
                    car = 0;
                }
            }
            else if(l2)
            {
                p->next = new ListNode(l2->val + car);
                p = p->next;
                l2 = l2->next;
                if(p->val >= 10)
                {
                    p->val -= 10;
                    car = 1;
                }
                else
                {
                    car = 0;
                }
            }
        }
        if(car == 1){
            p->next = new ListNode(1);
        }
        return pre->next;
    }
};
