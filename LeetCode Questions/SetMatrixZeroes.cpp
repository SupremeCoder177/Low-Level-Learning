#include <iostream>
#include <vector>
#include <set>


using namespace std;


class Solution {

    vector<vector<int>> searchOriginalZeroes(vector<vector<int>>& matrix, int n, int m){
        vector<vector<int>> out;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(matrix[i][j] == 0) out.push_back({i, j});
            }
        }
        return out;
    }

    set<int> get_unique_rows(vector<vector<int>> zeroes){
        set<int> out;
        for(auto v : zeroes){
            out.insert(v[0]);
        }
        return out;
    }

    set<int> get_unique_columns(vector<vector<int>> zeroes){
        set<int> out;
        for(auto v : zeroes){
            out.insert(v[1]);
        }
        return out;
    }

    public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> temp = searchOriginalZeroes(matrix, n, m);

        set<int> rows = get_unique_rows(temp);
        set<int> cols = get_unique_columns(temp);

        for(int row : rows){
            for(int i = 0; i < m; i++){
                matrix[row][i] = 0;
            }
        }

        for(int col : cols){
            for(int i = 0; i < n; i++){
                matrix[i][col] = 0;
            }
        }
    }
};


int main(){

    vector<vector<int>> temp = {
        {0, 1, 0},
        {1, 1, 1},
        {1, 1, 1}
    };

    Solution().setZeroes(temp);

    for(auto v : temp){
        for(int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}