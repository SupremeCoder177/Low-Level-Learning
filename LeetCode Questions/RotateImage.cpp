#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        
        vector<vector<int>> temp;
        for(int row = 0; row < matrix[0].size(); row++){
            vector<int> column_vector;
            for(int col = 0; col  < matrix.size(); col++){
                column_vector.push_back(matrix[row][col]);
            }
            temp.push_back(column_vector);
        }
        int size = matrix[0].size();

        int index = 0;
        int row = 0;
        while(index < size){
            int col = size - 1;
            for(auto v : temp){
                matrix[row][col] = v[index];
                col--;
            }
            row++;
            index++;
        }
    }
};

int main(){

    vector<vector<int>> val = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Solution().rotate(val);

    for(auto v : val){
        for(int i : v){
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}