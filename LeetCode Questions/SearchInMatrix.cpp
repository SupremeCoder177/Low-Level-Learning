#include <iostream>
#include <vector>


using namespace std;


class Solution {
    public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int l = 0, r = m;

        while(l < r){
            int index = ((r - l) / 2) + l;

            if(matrix[index][0] == target) return true;
            else{
                if(matrix[index][0] < target){
                    l = index + 1;
                }else{
                    r = index;
                }
            }
        }

        if(l == 0) return false;

        int start = 0, end = n;
        while(start < end){
            int index = (end - start) / 2 + start;

            if(matrix[l - 1][index] == target) return true;
            else{
                if(matrix[l - 1][index] < target){
                    start = index + 1;
                }else{
                    end = index;
                }
            }
        }
        return false;
    }
};


int main(){

    vector<vector<int>> temp = {
        {1, 3, 5, 7},
        {10 ,11, 16, 20},
        {23, 30, 34, 60}
    };

    cout << boolalpha;
    cout << Solution().searchMatrix(temp, 4);

    return 0;
}