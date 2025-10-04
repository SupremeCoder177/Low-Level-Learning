#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:
    void explore(vector<vector<char>> map, int row, int col, vector<vector<bool>>& seen){
        if(seen[row][col]) return;
        seen[row][col] = true;

        for(auto v : get_valid_cells(row, col, map)){
            explore(map, v[0], v[1], seen);
        }
    }


    vector<vector<int>> get_valid_cells(int row, int col, vector<vector<char>> map){
        vector<vector<int>> out;
        for(auto v : get_surrounding_points(row, col)){
            if(v[0] < map.size() && v[0] >= 0 && v[1] < map[0].size() && v[1] >= 0 && map[v[0]][v[1]] == '1') out.push_back(v);
        }
        return out;
    }


    vector<vector<int>> get_surrounding_points(int row, int col){
        return {{row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};
    }

    public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> seen;
        int count = 0;


        for(int i = 0; i < n; i++){
            vector<bool> temp;
            for(int j = 0; j < m; j++){
                temp.push_back(false);
            }
            seen.push_back(temp);
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == '0') continue;
                if(seen[i][j]) continue;
                count++;
                explore(grid, i, j, seen);
            }
        }
        return count;
    }
};


int main(){

    vector<vector<char>> temp = {{'1', '1', '0', '0', '0'},
                                 {'1', '1', '1', '1', '1'},
                                 {'0', '0', '1', '0', '0'},
                                 {'1', '1', '1', '1', '1'}
                                };

    cout << "Number of islands : " << Solution().numIslands(temp) << endl;

    return 0;
}