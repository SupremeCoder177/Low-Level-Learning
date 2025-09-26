#include <iostream>
#include <vector>

using namespace std;


class Solution {

    private:

    void recursiveAdd(vector<int> nums, vector<vector<int>>& out){
        if(nums.size() <= 0) return;

        vector<vector<int>> temp;
        vector<vector<int>> copy = out;
        out.clear();
        for(auto v : copy){
            for(int i = 0; i < nums.size(); i++){
                vector<int> curr_vec = v;
                curr_vec.push_back(nums[i]);
                temp.push_back(curr_vec);
                vector<int> new_nums = removeIndex(nums, i);
                recursiveAdd(new_nums, temp);
                for(auto v : temp) out.push_back(v);
                temp.clear();
            }
        }
    }

    vector<int> removeIndex(vector<int> nums, int index){
        nums.erase(nums.begin() + index);
        return nums;
    }

    public:
    vector<vector<int>> permute(vector<int>& nums) {
        
        vector<vector<int>> output;
        for(int i = 0; i < nums.size(); i++){
            vector<vector<int>> temp = {{nums[i]}};
            vector<int> new_nums = removeIndex(nums, i);
            recursiveAdd(new_nums, temp);
            for(auto v : temp) output.push_back(v);
        }
        
        return output;
        
    }
};


int main(){

    vector<int> temp = {1, 2, 3};
    for(auto v : Solution().permute(temp)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}