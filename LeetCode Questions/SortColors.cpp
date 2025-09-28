#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zeroes = 0;
        int ones = 0;
        for(int i : nums){
            switch(i){
                case 0: zeroes++; break;
                case 1: ones++; break;
                default: break;
            }
        }

        for(int i = 0; i < nums.size(); i++){
            if(zeroes > 0) {nums[i] = 0; zeroes--;}
            else if(ones > 0) {nums[i] = 1; ones--;}
            else nums[i] = 2;
        }
    }
};


int main(){

    vector<int> temp = {0, 1, 1, 2, 2, 0, 2};
    Solution().sortColors(temp);

    for(int i : temp) cout << i << " ";
    cout << endl;

    return 0;
}