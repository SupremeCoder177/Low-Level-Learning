#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> output = {-1, -1};
        if(nums.size() == 0) return output;
        if(nums.size() == 1){
            if(nums[0] != target) return output;
            else{
                output = {0, 0};
                return output;
            }
        }

        int left = 0, right = nums.size();
        int mid;
        while(left < right){
            mid = left + (right - left) / 2;
            if(nums[mid] == target) break;

            if(nums[left] < target){
                left = mid + 1;
            }
            else{
                right = mid ;
            }
        }

        if(nums[mid] != target) return output;
        else{
            left = mid, right = mid;
            while(left > 0){
                if(nums[left] != target) break;
                left--;
            }
            while(right < nums.size()){
                if(nums[right] != target) break;
                right++;
            }
            if(right >= nums.size()) right = nums.size() - 1;
            if(nums[left] != target) left++;
            if(nums[right] != target) right--;
            output = {left, right};
        }
        return output;
    }
};


int main(){

    vector<int> nums = {0, 1, 2, 3, 4, 4, 4};
    vector<int> temp = Solution().searchRange(nums, 2);

    for(int i : temp) cout << i << " ";
    cout << endl;

    return 0;
}