#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:
    vector<int> implementAddAlgorithm(vector<int> nums){
        vector<int> out;
        int n = nums.size();
        for(int i = 0; i < n - 1; i++){
            out.push_back((nums[i] + nums[i + 1]) % 10);
        }
        return out;
    }

    public:
    int triangularSum(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];

        vector<int> temp = nums;
        while(true){
            temp = implementAddAlgorithm(temp);
            if(temp.size() == 1) return temp[0];
        }
        return 0;
    }
};


int main(){

    vector<int> temp {1, 2, 3, 4, 5};
    cout << Solution().triangularSum(temp) << endl;

    return 0;
}