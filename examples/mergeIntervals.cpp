#include "../Vec.hpp"
#include <bits/stdc++.h>

void insertionSort(Vec<Vec<int>>& mat)
{
    int n = mat.size();
    for (int i = 1; i < n; ++i) {
        Vec<int> key = mat[i];
        int j = i - 1;
        while (j >= 0 && mat[j][0] > key[0]) {
            mat[j + 1] = mat[j];
            --j;
        }
        mat[j + 1] = key;
    }
}
Vec<Vec<int>> merge(Vec<Vec<int>>& intervals) 
{
    Vec<Vec<int>> res;
    
    res.push_back(intervals[0]);
    insertionSort(intervals);
    for(int i = 1; i < intervals.size(); ++i) {
        if(res[-1][1] >= intervals[i][0]){
            res[-1][1] = std::max(res[-1][1],intervals[i][1]);

        }
        else{
            res.push_back(intervals[i]);
        }
    }
    return res;
}

int main()
{
    Vec<Vec<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    Vec<Vec<int>> res = merge(intervals);
    std::cout << res << '\n';
}
