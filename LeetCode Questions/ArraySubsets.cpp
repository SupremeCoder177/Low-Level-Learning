#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> output = {{}};
        int input_size = 1;
        int n = nums.size();
        while(input_size <= n){
            for(int i = 0; i < n; i += input_size){
                vector<int> temp;
                for(int j = i; j < i + input_size; j++){
                    temp.push_back(nums[j]);
                }
                output.push_back(temp);
            }
            input_size++;
        }
        return output;
    }
};


int main(){

    vector<int> temp = {1, 2, 3};
    for(auto v : Solution().subsets(temp)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}