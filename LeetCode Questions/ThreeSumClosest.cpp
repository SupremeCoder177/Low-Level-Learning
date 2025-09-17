#include <iostream>
#include <vector>


class Solution{

    public:

    void quickSort(std::vector<int>& nums, int start, int end) {
        if (start >= end) return;

        int pivot = nums[end];
        int swap_ptr = start - 1;

        for (int comp_ptr = start; comp_ptr < end; comp_ptr++) {
            if (nums[comp_ptr] < pivot) {
                swap_ptr++;
                std::swap(nums[swap_ptr], nums[comp_ptr]);
            }
        }

        swap_ptr++;
        std::swap(nums[swap_ptr], nums[end]);

        quickSort(nums, start, swap_ptr - 1);
        quickSort(nums, swap_ptr + 1, end);
    }


    int threeSumClosest(std::vector<int>& nums, int target){
        quickSort(nums, 0, nums.size() - 1);
        
        int min_dis = -1;
        int size = nums.size();
        int closest = nums[0] + nums[1] + nums[2];

        for(int i = 0; i < size; i++){
            int start_ptr = i + 1;
            int end_ptr = size - 1;
            while(start_ptr < end_ptr){

                int sum = nums.at(i) + nums.at(start_ptr) + nums.at(end_ptr);

                if(abs(target - sum) < abs(target - closest)){
                    closest = sum;
                }
                if(sum < target){
                    start_ptr++;
                }else if(sum > target){
                    end_ptr--;
                }else{
                    return target;
                }
            }
        }
        return closest;
    }

};


int main(){
    std::vector<int> nums;
    nums.push_back(-1);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(-4);

    int temp = Solution().threeSumClosest(nums, 1);
    std::cout << "tmp : " << temp << std::endl;
    // Solution().quickSort(nums, 0, nums.size());
    // for(int i = 0; i < nums.size(); i++){
    //     std::cout << nums.at(i) << std::endl;
    // }

    return 0;
}