#include <vector>
using namespace std;

/*
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
 */
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int n):val(n),left(nullptr),right(nullptr){}
};
/*
已知的是，先序遍历的第一个节点，是当前树的根节点
该树没有重复值，因此在知道根节点的情况下，可以将先序遍历序列和中序遍历序列由根节点划分开
分别得到左子树和右子树的先序遍历序列、中序遍历序列
由左(右)子树的先序遍历序列和中序遍历序列可以得到该子树的根节点。
迭代直至子树为空，则可以求出所有子树的根节点，即可以重建该树。
*/
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