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