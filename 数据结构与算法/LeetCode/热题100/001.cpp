#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;
/*
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的
那两个整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
*/
class solution
{
public:
/*
思路：暴力遍历时间复杂度大约是o(nlog(n))，或者采用哈希,时间复杂度为o(n)。
*/
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> result;
        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = i + 1; j < nums.size(); ++j)
            {
                if (target == nums[i] + nums[j])
                {
                    result.push_back(i);
                    result.push_back(j);
                }
            }
        }
        return result;
    }
    vector<int> hash_for_twosum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hmap;
        int i = 0;
        vector<int> result;
        for (auto val : nums)
        {
            hmap[target - val] = i++;
        }
        i = 0;
        for (auto val : nums)
        {
            if (hmap.find(val) != hmap.end())
            {
                if (i != hmap[val])
                {
                    result.push_back(i);
                    result.push_back(hmap[val]);
                    break;
                }
            }
            ++i;
        }
        return result;
    }
};