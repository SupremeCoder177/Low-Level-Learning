#include <iostream>
#include <vector>
#include <set>

using namespace std;


class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        set<vector<int>> temp;
        vector<vector<int>> copy;
        for(auto v : intervals) temp.insert(v);
        for(auto v : temp) copy.push_back(v);
        vector<vector<int>> output = {copy[0]};

        int curr_interval_ptr = 0;
        int check_interval_ptr = 1;
        int n = copy.size();
        while(check_interval_ptr < n){
            if(copy[check_interval_ptr][0] <= output[curr_interval_ptr][1]){
                if(copy[check_interval_ptr][1] > output[curr_interval_ptr][1]) output[curr_interval_ptr][1] = copy[check_interval_ptr][1];
            }else{
                output.push_back(copy[check_interval_ptr]);
                curr_interval_ptr++;
            }
            check_interval_ptr++;
        }
        return output;
    }
};


int main(){

    vector<vector<int>> temp = {{1, 4}, {1, 4}};
    for(auto v : Solution().merge(temp)){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}