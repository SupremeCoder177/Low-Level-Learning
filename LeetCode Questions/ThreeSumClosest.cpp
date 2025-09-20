#include <iostream>
#include <vector>


class Solution{

    public:
    int threeSumClosest(vector<int>& nums, int target){

        bool first_iter = true;
        int min_dis = 0;

        for(int i = 0; i < nums.size(); i++){
            for(int j = 0; j < nums.size(); j++){
                if(i == j) continue;
                for(int k = 0; k < nums.size(); k++){
                    if(i == k || k == j) continue;

                    int temp = nums.at(i) + nums.at(j) + nums.at(k);
                    if(first_iter) {
                        min_dis = target - temp;
                        first_iter = false;
                    }else{
                        if(abs(target - temp) < min_dis && abs(temp) != target) min_dis = target - temp;
                    }
                }
            }
        }
        return min_dis
    }

};


int main(){
    

    return 0;
}