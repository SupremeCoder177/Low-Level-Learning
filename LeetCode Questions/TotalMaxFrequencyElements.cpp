#include <map>
#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        map<int, int> temp;
        for(int i : nums){
            if(temp.find(i) != temp.end()){
                temp[i]++;
            }else{
                temp[i] = 1;
            }
        }

        int max = 0;
        for(auto [k, v] : temp){
            if(v > max){
                max = v;
            }
        }

        int output = 0;
        for(auto [k, v] : temp){
            if(v == max){
                output += v;
            }
        }
        return output;
    }
};


int main(){

    vector<int> temp = {1, 2, 2, 3, 1, 4};
    int output = Solution().maxFrequencyElements(temp);

    cout << output << endl;

    return 0;
}