#include <iostream>
#include <vector>
#include <set>


using namespace std;


class Solution {
    private:
    void recursiveAdd(set<vector<int>>& out, vector<int> in, vector<int> storage, int maxLen){
        if(storage.size() >= maxLen) {
            mergeSort(storage);
            out.insert(storage);
            return;
        }
        int n = in.size();
        for(int i = 0; i < n; i++){
            vector<int> copy = storage;
            copy.push_back(in[i]);
            recursiveAdd(out, removeAndReturn(in, i), copy, maxLen);
        }
    }
    
    vector<int> removeAndReturn(vector<int> nums, int index){
        nums.erase(nums.begin() + index);
        return nums;
    }

    void mergeSort(vector<int>& arr){
        if(arr.size() <= 1) return;

        vector<int> left, right;
        int n = arr.size();
        for(int i = 0; i < n; i++){
            if(i < n / 2) left.push_back(arr[i]);
            else{
                right.push_back(arr[i]);
            }
        }

        mergeSort(left);
        mergeSort(right);
        merge(arr, left, right);
    }

    void merge(vector<int>& arr, vector<int> left, vector<int> right){
        arr.clear();
        int l = 0, r = 0;

        while(l < left.size() && r < right.size()){
            if(left[l] < right[r]){
                arr.push_back(left[l]);
                l++;
            }else{
                arr.push_back(right[r]);
                r++;
            }
        }

        while(l < left.size()){
            arr.push_back(left[l]);
            l++;
        }
        while(r < right.size()){
            arr.push_back(right[r]);
            r++;
        }
    }

    public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> output;
        set<vector<int>> temp;

        output.push_back(vector<int>{});
        int n = nums.size();
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < n; j++){
                vector<int> copy = {nums[j]};
                recursiveAdd(temp, removeAndReturn(nums, j), copy, i);
            }        
        }
        for(vector<int> v : temp){
            output.push_back(v);
        }
        return output;
    }

};


int main(){

    vector<int> temp = {0};
    for(auto v : Solution().subsets(temp)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}