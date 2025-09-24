#include <iostream>
#include <vector>
#include <set>

using namespace std;


class Solution {

    private:
    void backtrackSum(int target, vector<int> candidates, vector<vector<int>>& output, vector<int> nums){
        for(int cand : candidates){
            vector<int> temp = nums;
            temp.push_back(cand);
            if(cand < target){
                backtrackSum(target - cand, candidates, output, temp);
            }else{
                if(cand == target){
                    output.push_back(temp);
                }
            }
        }
    }

    void quickSort(vector<int>& nums, int start, int end){
        if(end <= start) return;

        int swap_ptr = start - 1;
        int comp_ptr = start;
        int chosen_one = nums[end];
        while(comp_ptr < end){
            if(nums[comp_ptr] < chosen_one){
                swap_ptr++;
                int temp = nums[swap_ptr];
                nums[swap_ptr] = nums[comp_ptr];
                nums[comp_ptr] = temp;
            }
            comp_ptr++;
        }
        swap_ptr++;
        int temp = nums[swap_ptr];
        nums[swap_ptr] = chosen_one;
        nums[end] = temp;
        quickSort(nums, start, swap_ptr - 1);
        quickSort(nums, swap_ptr + 1, end);
    }

    public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> output;
        for(int num : candidates){
            vector<int> temp = {num};
            if(num < target){
                backtrackSum(target - num, candidates, output, temp);
            }
            else{
                if(num == target) {
                    output.push_back(temp);
                }
            }
        }
        set<vector<int>> uniques;
        for(auto vec : output){
            quickSort(vec, 0, vec.size() - 1);
            uniques.insert(vec);
        }
        output.clear();
        for(auto vec : uniques){
            output.push_back(vec);
        }
        return output;
    }
};

int main(){

    vector<int> temp = {2, 3, 6, 7};
    for(auto v : Solution().combinationSum(temp, 7)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}