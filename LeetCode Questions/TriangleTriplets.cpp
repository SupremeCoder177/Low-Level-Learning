#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


class Solution {

    private:
    void mergeSort(vector<int>& nums){
        if(nums.size() <= 1) return;

        vector<int> left, right;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(i < n / 2) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }

        mergeSort(left);
        mergeSort(right);
        merge(left, right, nums);
    }

    void merge(vector<int> left, vector<int> right, vector<int>& arr){
        int i = 0, l = 0, r = 0;
        while(l < left.size() && r < right.size()){
            if(left[l] < right[r]){
                arr[i++] = left[l++];
            }else{
                arr[i++] = right[r++];
            }
        }
        while(l < left.size()){
            arr[i++] = left[l++];
        }
        while(r < right.size()){
            arr[i++] = right[r++];
        }
    }

    
    public:
    int triangleNumber(vector<int>& nums) {
        if(nums.size() < 3) return 0;
        mergeSort(nums);
        int output = 0;
        int n = nums.size();
        for(int i = n - 1; i >= 2; i--){
            int j = 0, k = i - 1;
            while(j < k){
                if(nums[j] + nums[k] > nums[i]){
                    output += (k - j);
                    k--;
                }else{
                    j++;
                }
            }
        }

        return output;
    }
};


int main(){

    vector<int> temp = {2, 2, 3 ,4};
    int out = Solution().triangleNumber(temp);
    cout << out << endl;

    return 0;
}