#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:
    bool check_adjacents(vector<vector<int>> seen, vector<int> cell){
        vector<vector<int>> cells = {get_point(cell, -1, 0), get_point(cell, 1, 0), get_point(cell, 0, -1), get_point(cell, 0, 1)};

        for(auto v : seen){
            for(auto c : cells){
                if(v == c) return true;
            }
        }

        return false;
    }

    vector<int> get_point(vector<int> coord, int dx, int dy){
        coord[0] += dx;
        coord[1] += dy;
        return coord;
    }

    public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int count = 0;
        vector<vector<int>> islands;        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == '1'){
                    vector<int> temp = {i, j};
                    islands.push_back(temp);
                    if(!check_adjacents(islands, temp)) count++;
                }
            }
        }
        return count;
    }
};


int main(){

    vector<vector<char>> temp = {{'1', '1', '0', '0', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '1', '0', '0'},
                                 {'0', '0', '0', '1', '1'}
                                };

    cout << "Number of islands : " << Solution().numIslands(temp) << endl;

    return 0;
}