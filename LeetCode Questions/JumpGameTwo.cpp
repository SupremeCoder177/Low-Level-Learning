#include <iostream>
#include <vector>

using namespace std;


class Solution {

    int findMaxIndex(vector<int> nums, int begin, int end){
        int max = begin;
        for(int i = begin; i <= end; i++){
            if(nums[i] > nums[max]) max = i;
        }
        return max;
    }

    public:
    int jump(vector<int>& nums) {
        int index = 0;
        int jumps = 0;
        int n = nums.size();
        while(index < n - 1){
            if(nums[index] + index < n){
                index = findMaxIndex(nums, index + 1, index + nums[index]);
            }else{
                index = findMaxIndex(nums, index + 1, n - 1);
            }
            jumps++;
        }
        return jumps;
    }
};


int main(){

    vector<int> temp = {3, 2, 1};
    cout << Solution().jump(temp) << endl;

    return 0;
}