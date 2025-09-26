#include <vector>
#include <iostream>

using namespace std;


class Solution {

    public:
    int binarySearch(vector<int> nums, int target){
        int left = 0, right = nums.size();
        while(left < right){
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] < target){
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        return -1;
    }

    public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> output = {-1, -1};
        if(nums.size() == 0) return output;
        else if(nums.size() == 1){
            if(nums[0] != target) return output;
            else{
                output = {0, 0};
                return output;
            }
        }
        int temp = binarySearch(nums, target);
        if(temp == -1) return output;

        int left = temp, right = temp;
        while(left >= 0 && nums[left] == target) left--;
        while(right < nums.size() && nums[right] == target) right++;
        output = {left + 1, right - 1};
        
        return output;
    }
};


int main(){

    vector<int> nums = {0, 1, 2, 3, 4, 4, 4};
    vector<int> temp = Solution().searchRange(nums, 4);

    for(int i : temp) cout << i << " ";
    cout << endl;

    return 0;
}