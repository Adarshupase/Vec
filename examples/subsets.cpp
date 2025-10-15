#include "../Vec.hpp"


void dfs(int i,Vec<Vec<int>>& ans,Vec<int> &cur,Vec<int>& nums)
{
    if(i == nums.size())
    {
        ans.push_back(cur);
        return ;
    }
    cur.push_back(nums[i]);
    dfs(i+1,ans,cur,nums);
    cur.pop_back();
    dfs(i+1,ans,cur,nums);
}



Vec<Vec<int>> subsets(Vec<int>& nums)
{
    Vec<Vec<int>> ans;
    Vec<int> cur;
    dfs(0,ans,cur,nums);
    return ans;


}

int main()
{
   
    Vec<int> nums({1,2,3});
    Vec<Vec<int>> ans = subsets(nums);
    std::cout << "ans = " << ans << '\n';


}

