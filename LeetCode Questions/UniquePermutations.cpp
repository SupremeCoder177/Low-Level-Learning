#include <iostream>
#include <set>
#include <vector>

using namespace std;


class Solution {

    private:
    void recursiveAdd(vector<int> nums, set<vector<int>>& out){
        if(nums.size() <= 0) return;

        set<vector<int>> copy = out;
        set<vector<int>> temp;
        out.clear();
        for(auto v : copy){
            for(int i = 0; i < nums.size(); i++){
                vector<int> new_vec = v;
                v.push_back(nums[i]);
                vector<int> new_nums = removeIndex(nums, i);
                temp.insert(new_vec);
                recursiveAdd(new_nums, temp);
                for(auto v : temp) out.insert(v);
                temp.clear();
            }
        }
    }


    vector<int> removeIndex(vector<int> nums, int index){
        nums.erase(nums.begin() + index);
        return nums;
    }

    public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int>> temp;
        vector<vector<int>> output;

        for(int i = 0; i < nums.size(); i++){
            vector<int> copy = {nums[i]};
            temp.insert(copy);
            vector<int> new_nums = removeIndex(nums, i);
            recursiveAdd(new_nums, temp);
        }

        for(auto v : temp) output.push_back(v);

        return output;
    }
};


int main(){

    vector<int> temp = {1, 1, 2};
    for(auto v : Solution().permuteUnique(temp)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}