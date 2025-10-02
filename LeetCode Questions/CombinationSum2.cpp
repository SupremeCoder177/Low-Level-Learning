#include <iostream>
#include <vector>
#include <set>


using namespace std;


class Solution {

    private:
    void backtrackSum(vector<int>& candidates, vector<int> nums, int target, set<vector<int>>& output_holder){
        for(int i = 0; i < candidates.size(); i++){
            vector<int> temp = nums;
            temp.push_back(candidates[i]);
            if(candidates[i] < target){
                vector<int> temp2 = removeAndReturnVector(candidates, i);
                backtrackSum(temp2, temp, target - candidates[i], output_holder);
            }else{
                if(candidates[i] == target){ 
                    mergeSort(temp);
                    output_holder.insert(temp);
                }
            }
        }
    }

    void mergeSort(vector<int>& nums){
        if(nums.size() <= 1) return;

        vector<int> left_arr;
        vector<int> right_arr;
        int n = nums.size() / 2;

        for(int i = 0; i < nums.size(); i++){
            if(i < n) left_arr.push_back(nums[i]);
            else right_arr.push_back(nums[i]);
        }

        mergeSort(left_arr);
        mergeSort(right_arr);
        merge(left_arr, right_arr, nums);
    }

    void merge(vector<int> left_arr, vector<int> right_arr, vector<int>& arr){
        int l = 0, r = 0, i = 0;

        while(l < left_arr.size() && r < right_arr.size()){
            if(left_arr[l] < right_arr[r]){
                arr[i] = left_arr[l];
                l++;
            }else{
                arr[i] = right_arr[r];
                r++;
            }
            i++;
        }

        while(l < left_arr.size()){
            arr[i] = left_arr[l];
            l++;
            i++;
        }

        while(r < right_arr.size()){
            arr[i] = right_arr[r];
            r++;
            i++;
        }
    }

    vector<int> removeAndReturnVector(vector<int> nums, int index){
        nums.erase(nums.begin() + index);
        return nums;
    }

    public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> output;
        set<vector<int>> temp;

        for(int i = 0; i < candidates.size(); i++){
            vector<int> holder = {candidates[i]};
            if(candidates[i] < target){
                vector<int> temp2 = removeAndReturnVector(candidates, i);
                backtrackSum(temp2, holder, target - candidates[i], temp);
            }else if(candidates[i] == target) temp.insert({target});
        }

        for(auto v : temp) {
            output.push_back(v);
        }

        return output;
    }
};


int main(){

    vector<int> temp = {2, 5, 2, 1, 2};
    for(auto v : Solution().combinationSum2(temp, 5)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}