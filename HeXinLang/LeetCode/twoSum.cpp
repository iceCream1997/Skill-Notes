#include <iostream>
#include <vector>
#include <list>
using namespace std;
class solution{
public:
    vector<int> twoSum(vector<int>& nums,int target)
    {
        vector<int> result;
        for(int i = 0; i < nums.size(); ++i)
        {
            for(int j = i+1; j < nums.size(); ++j)
            {
                cout << "comparing " << nums[i] << " and " << nums[j] 
                    << " with the " << target << endl;
                if(target == nums[i] + nums[j])
                {
                    result.push_back(i);
                    result.push_back(j);
                }
            }
        }
        return result;
    }
};