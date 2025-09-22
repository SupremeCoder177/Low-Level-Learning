#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();

        while(left < right){
            int mid = left + (right - left) / 2;

            if(nums[mid] == target) return mid;

            if(nums[mid] < target){
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        return left;
    }
};


int main(){

    vector<int> nums = {1, 3, 5, 6};
    int temp = Solution().searchInsert(nums, 5);

    cout << temp << endl;

    return 0;   
}