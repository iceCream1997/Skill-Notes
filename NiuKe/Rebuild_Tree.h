#include "head.h"
using namespace std;

/*
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
 */

//思路：已知前序遍历的第一个节点是当前树的根节点，则可以由此得出根节点的左子树和右子树。
//采用递归，可得出答案.
//即，该根节点的左子节点为左子树的先序和中序调用函数得到的结果。
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int n):val(n),left(nullptr),right(nullptr){}
};

class solution{
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin)
    {
        if(!pre.size())
            return nullptr;
        else if(pre.size() == 1)
            return new TreeNode(*pre.begin());
        TreeNode* head = new TreeNode(*pre.begin());
        int i = 0;
        vector<int> vinl,vinr,prel,prer;
        while(pre[0] != vin[i]){
                ++i;
        }
        for (auto j = 0; j != pre.size(); ++j)
        {
            if (j < i)
            {
                prel.push_back(pre[j + 1]);
                vinl.push_back(vin[j]);
            }
            else if (j == i);
            else
            {
                prer.push_back(pre[j]);
                vinr.push_back(vin[j]);
            }
        }
        head->left = reConstructBinaryTree(prel,vinl);
        head->right = reConstructBinaryTree(prer,vinr);
        return head;
    }
};