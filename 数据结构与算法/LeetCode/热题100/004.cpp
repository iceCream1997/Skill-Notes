#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
/*
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。
*/
class sloution{
/*
思路：题目给定了时间复杂度为log(m+n)，很容易想到二分。
*/
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        double result(0);
    }
};

int main()
{
    unordered_map<int,int> a{{1,2},{3,4},{8,9}};
    cout << a.size() << endl;
    cout << a.bucket_count() << endl;
    cout << a.load_factor() << endl;
    cout << a.bucket_size(1) << endl;
    cout << a.bucket_size(2) << endl;
    cout << a.bucket_size(3) << endl;
    cout << a.bucket_size(4) << endl;
    cout << a.bucket_size(5) << endl;
    
}