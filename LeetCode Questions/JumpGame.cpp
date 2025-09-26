#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size() <= 1) return true;
        if(nums[0] == 0) return false;
        int index = 0;
        int n = nums.size();
        while(index < n - 1){
            if(nums[index] + index >= n - 1) return true;

            int max = index + 1;
            for(int i = index + 1; i <= index + nums[index]; i++){
                if(i < n && nums[i] >= nums[max]) max = i;
            }
            if(nums[max] == 0) {
                if(nums[index] + index >= n - 1) return true;
                else return false;
            }
            index = max;

            cout << "Index : " << index << " Max : " << max << " Nums[max] : " << nums[max] << endl;
        }
        return false;
    }
};


int main(){

    vector<int> temp = {4,2,0,0,1,1,4,4,4,0,4,0};
    cout << boolalpha;
    cout << Solution().canJump(temp) << endl;

    return 0;
}