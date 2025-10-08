#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>


using namespace std;


class Solution {

    private:

    int search(vector<int> nums, int target, int size){
        int ptr = size / 2;
        int left = 0, right = size;
        while(left < right){
            if(nums[ptr] == target) return ptr;
            else{
                if(nums[ptr] < target){
                    left = ptr + 1;
                }else{
                    right = ptr;
                }
            }
            ptr = ((right - left) / 2) + left;
        }
        return ptr;
    }

    public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());

        int n = spells.size();
        int m = potions.size();
        vector<int> output (n);
        
        int spell_ptr = 0;
        
        while(spell_ptr < n){
            float temp = (float) success / spells[spell_ptr];
            int target = (int) temp;
            if(temp - target > 0){
                target++;
            }

            output[spell_ptr] += m - search(potions, target, m);
            spell_ptr++;
        }
        return output;
    }
};


int main(){

    vector<int> temp1 = {3, 1, 2};
    vector<int> temp2 = {8, 5, 8};
    int success = 16;

    for(int i : Solution().successfulPairs(temp1, temp2, success)){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}