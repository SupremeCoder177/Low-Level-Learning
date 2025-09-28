#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:
    void radixSort(vector<int>& nums){
        int exp = 1;

        int max = nums[0];
        for(int i : nums) if(i > max) max = i;

        vector<int> copy(nums.size());

        while(max / exp > 0){

            int count[10] = {0};

            for(int i : nums){
                int index = (i / exp) % 10;
                count[index]++;
            }

            for(int i = 1; i < 10; i++) count[i] += count[i - 1];

            for(int i = nums.size() - 1; i >= 0; i--){
                int index = (nums[i] / exp) % 10;
                copy[count[index] - 1] = nums[i];
                count[index]--;
            }

            nums = copy;

            exp *= 10;
        }
    }

    public:
    int largestPerimeter(vector<int>& nums) {
        radixSort(nums);
        int largest = 0;
        int n = nums.size();

        for(int i = n - 1; i >= 2; i--){
            int left = 0, right = i - 1;
            while(left < right){

                if(nums[right] + nums[left] > nums[i]){
                    largest = max(largest, nums[i] + nums[left] + nums[right]);
                    
                }
                left++;
            }
        }

        return largest;
    }
};


int main(){

    vector<int> temp = {2, 6, 2, 5, 4, 15, 1};
    cout << Solution().largestPerimeter(temp) << endl;

    return 0;
}