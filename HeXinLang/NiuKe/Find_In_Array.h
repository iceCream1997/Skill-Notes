/*题目描述
在一个二维数组中（每个一维数组的长度相同），
每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。请完成一个函数，
输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 */
#include "head.h"
using namespace std;
class solution{

//思路： 该数组是有序的，虽然遍历可以做到，但显然没有使用到有序这一条件。且时间复杂度较高
//从该数组的左下角开始查找，因为左下角是一个临界点，比他小的必然在上面，比他大的必然在右边。
//如果target小于该值，则往上移动一格，如果大于，则往右移动一格，直至找到或者数组找完为止。
public:
    bool Find(int target,vector<vector<int> > array)
    {
        auto m = array.size();
        if( m == 0) return false;
        auto n = array[0].size();
        if( n == 0) return false;
        int i = m-1, j = 0;
        while(i >= 0 && j < n)
        {
            if(target == array[i][j])
                return true;
            else if(target < array[i][j])
                --i;
            else if(target > array[i][j])
                ++j;
        }
        return false;
    }
};