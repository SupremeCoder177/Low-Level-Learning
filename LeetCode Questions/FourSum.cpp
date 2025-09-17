#include <vector>
#include <iostream>
#include <stdlib.h>


class Solution{

    public:
    void mergeSort(std::vector<int>& nums){
        if(nums.size() <= 1) return;


        std::vector<int> leftArr;
        std::vector<int> rightArr;
        int middle = nums.size() / 2;
    
        for(int i = 0; i < nums.size(); i++){
            if(i < middle){
                leftArr.push_back(nums.at(i));
            }else{
                rightArr.push_back(nums.at(i));
            }
        }

        mergeSort(leftArr);
        mergeSort(rightArr);
        merge(leftArr, rightArr, nums);
    }

    void merge(std::vector<int>& leftArr, std::vector<int>& rightArr, std::vector<int>& arr){
        int l = 0, r = 0, i = 0;

        while(l < leftArr.size() && r < rightArr.size()){
            if(leftArr[l] < rightArr[r]){
                arr[i] = leftArr[l];
                l++;
            }else{
                arr[i] = rightArr[r];
                r++;
            }
            i++;
        }

        while(l < leftArr.size()){
            arr[i] = leftArr[l];
            l++;
            i++;
        }

        while(r < rightArr.size()){
            arr[i] = rightArr[r];
            r++;
            i++;
        }
    }

    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target){
        mergeSort(nums);
        std::vector<std::vector<int>> output;
        int start_ptr = 0;
        int end_ptr = nums.size() - 1;

        while(start_ptr < end_ptr){
            int left_ptr = start_ptr + 1;
            int right_ptr = end_ptr - 1;
            int sum = 0;
            while(left_ptr < right_ptr){
                sum = nums[start_ptr] + nums[end_ptr] + nums[left_ptr] + nums[right_ptr];
                if(sum == target) {
                    std::vector<int> temp;
                    temp.push_back(nums[start_ptr]);
                    temp.push_back(nums[end_ptr]);
                    temp.push_back(nums[left_ptr]);
                    temp.push_back(nums[right_ptr]);
                    output.push_back(temp);
                }else if(sum < target){
                    left_ptr++;
                }else{
                    right_ptr--;
                }
            }
            if(sum < target){
                start_ptr++;
            }else{
                end_ptr--;
            }
        }
        return output;
    }

};



int main(int argc, char* argv[]){

    std::vector<int> nums = {1, 0, -1, 0, -2 , 2};
    
    // char* temp;
    // for(int i = 1; i < argc - 1; i++){
    //     int add = strtol(argv[i], &temp, 10);
    //     nums.push_back(add);
    // }
    // int target = strtol(argv[argc - 1], &temp, 10);
    
    std::cout << "running" << std::endl;
    std::vector<std::vector<int>> output = Solution().fourSum(nums, 0);
    std::cout << "finished" << std::endl;

    for(int i = 0; i < output.size(); i++){
        for(int num : output[i]){
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}