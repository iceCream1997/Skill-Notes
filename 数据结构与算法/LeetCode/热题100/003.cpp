#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
/*
给定一个字符串，请你找出其中不含有重复字符的最长子串的长度。
示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是子串的长度，"pwke" 是一个子序列，不是子串
*/
class solution{
/*
思路：从每一个字符开始，直到第一个重复字符出现，此字符串为从当前字符开始的最长子串。
依次对每一个字符计算其最长子串长度。求出结果。(暴力解超时)

算法可以优化，即每次向前扫描得出当前出现重复字符时，我们选择了当前扫描出发点的下一个字符，
实际上，从这个字符出发的字符串不会比之前的字符串长，因为还是会出现重复字符，
且该字符串至少比之前长度少一，因为我们往后移动了一次起始位置。
因此我们改进为在出现重复字符时，下一扫描出发点为重复字符的下一尾置。

继续优化：
    该算法主要是，hashmap消耗的内存以及时间，hashmap主要是作为判断是否重复，以及找到下一位置的作用，
因此我们可以找另外一种方式来实现它的功能。实际上在扫描的时候，如果我们将初始位置依次遍历，改为结束位置依次遍历
就可以不用保存扫描的字符串。
例如起始设置结束位置为1，那么刚开始遍历时，可能出现两种情况，即当n为2时，遍历是否实现重复。
如果出现重复，我们记录并判断当前字符串的长度，并跳过它。如果不重复，下一次遍历时，还从之前的起始位置开始。
即可以保证，当前扫描的字符串，绝对不会出现扫描不到的情况，因为，假如出现重复，那么一定在之前的扫描中得到了重复的结果并跳过了它。
并且可以不用保存扫描的字符串，只需要判断当前扫描的字符是否与目标字符重复即可。
*/
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char,string::iterator> mymap;
        int maxlen = 0;
        for(auto b = s.begin(); b != s.end(); ++b)
        {
            auto val = b;
            int len = 0;
            while(mymap.find(*val) == mymap.end() && val != s.end())
            {
                mymap[*val] = val;
                ++val;
                ++len;
            }
            if(len > maxlen)
                maxlen = len;
            if(mymap.find(*val) != mymap.end())
            {
                b = mymap[*val];
            }
            mymap.clear();
        }
        return maxlen;
    }


    
    int bestfunc(string s)
    {
        int size,i = 0, j,k, max = 0;
        size = s.size();
        for(j = 0; j < size; ++j)
        {
            for(k = i; k < j; ++k)
            {
                if(s[k] == s[j])
                {
                    i = k+1;
                    break;
                }
            }
            if(j-i+1 > max)
                max = j-i+1;
        }
        return max;
    }
};