#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:
    void sortIntervals(vector<vector<int>>& intervals){
        if(intervals.size() <= 1) return;

        vector<vector<int>> left, right;
        int m = intervals.size();
        for(int i = 0; i < m; i++){
            if(i < m / 2) left.push_back(intervals[i]);
            else right.push_back(intervals[i]);
        }

        sortIntervals(left);
        sortIntervals(right);
        merge(left, right, intervals);
    }

    void merge(vector<vector<int>>& left, vector<vector<int>>& right, vector<vector<int>>& arr){
        int l = 0, r = 0;
        int m = left.size(), n = right.size();
        arr.clear();
        while(l < m && r < n){
            if(left[l][0] != right[r][0]){
                if(left[l][0] < right[r][0]){
                    arr.push_back(left[l]);
                    l++;
                }else{
                    arr.push_back(right[r]);
                    r++;
                }
            }else{
                if(left[l][1] < right[r][1]){
                    arr.push_back(left[l]);
                    l++;
                }else{
                    arr.push_back(right[r]);
                    r++;
                }
            }
        }
        while(l < m){
            arr.push_back(left[l]);
            l++;
        }
        while(r < n){
            arr.push_back(right[r]);
            r++;
        }
    }

    public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sortIntervals(intervals);
        int count = 0;

        for(int i = 0; i < intervals.size(); i++){
            int this_one = 0;
            
            if(i - 1 >= 0){
                if(intervals[i - 1][0] <= intervals[i][0] && intervals[i][0] <= intervals[i - 1][1]){
                    this_one++;
                }
            }

            if(i + 1 < intervals.size()){
                if(intervals[i + 1][0] <= intervals[i][1] && intervals[i][1] <= intervals[i + 1][1]) {
                    this_one--;
                }
            }
            count += this_one;
        }

        return count;
    }
};


int main(int argc, char* argv[]){

    vector<vector<int>> temp = {{1, 3}, {1, 4}, {2, 5}, {3, 5}};
    cout << Solution().intersectionSizeTwo(temp) << endl;

    return 0;
}