#include <iostream>
#include <vector>

using namespace std;


class Solution {

    private:
    int getTreeMin(vector<vector<int>>& tree, int row_index, int index){
        if(row_index == tree.size() - 1){
            if(index + 1 < tree[row_index].size()){
                return tree[row_index][index] < tree[row_index][index + 1] ? tree[row_index][index] : tree[row_index][index + 1];
            }else{
                return tree[row_index][index];
            }
        }
        if(index + 1 < tree[row_index].size()){
            int output1 = tree[row_index][index];
            int output2 = tree[row_index][index + 1];
            int temp1 = getTreeMin(tree, row_index + 1, index);
            int temp2 = getTreeMin(tree, row_index + 1, index + 1);
            int min = output1 + temp1;
            if(output2 + temp2 < min)  min = output2 + temp2;
            return min;
        }
        else{
            int temp1 = tree[row_index][index];
            int temp2 = getTreeMin(tree, row_index + 1, index);
            return temp1 + temp2;
        }
    }

    public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() == 1) return triangle[0][0];
        
        int index = 0;
        int output1 = triangle[0][0];
        int output2 = triangle[0][0];

        int temp1 = getTreeMin(triangle, 1, 0);
        int temp2 = getTreeMin(triangle, 1, 1);

        output1 += temp1;
        output2 += temp2;

        return output1 < output2 ? output1 : output2;
    }
};


int main(){

    vector<vector<int>> temp = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << Solution().minimumTotal(temp) << endl;

    return 0;
}