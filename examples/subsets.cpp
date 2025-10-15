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


// typedef struct {
//     std::string name;
//     unsigned int age;
// }Person;
// class Animal{
//     public:
//         std::string m_name;
//         unsigned int m_age;

// };
//  Person p{"Tom",45};
//     Vec<Person *> persons;
//     Animal dog{"Dog",12};
//     Vec<Animal> animals;
//     animals.push_back(dog);
//     persons.push_back(&p);
//     for(auto &p : persons)
//     {
//         std::cout << p->name << '\n';
//         std::cout << p->age << '\n';
//     }
//     for(auto &a : animals)
//     {
//         std::cout << a.m_name << '\n';
//         std::cout << a.m_age << '\n';
//     }
