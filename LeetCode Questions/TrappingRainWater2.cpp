#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:
    bool checkLowest(vector<vector<int>> heightMap, int row, int col){
        if(row == 0 || row == heightMap.size() - 1) return false;
        if(col == 0 || col == heightMap[0].size() - 1) return false;

        vector<vector<int>> points = {{row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};
        for(auto v : points){
            if(heightMap[v[0]][v[1]] < heightMap[row][col]) return false;
        }
        return true;
    }

    bool checkSecondLowest(vector<vector<int>> heightMap, int row, int col){
        if(row == 0 || row == heightMap.size() - 1) return false;
        if(col == 0 || col == heightMap[0].size() - 1) return false;

        vector<vector<int>> points = {{row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};
        int num_bigger = 0;
        for(auto v : points){
            if(heightMap[v[0]][v[1]] > heightMap[row][col]) num_bigger++;
        }
        return num_bigger == 3;
    }

    bool seenAlready(vector<vector<int>> seen, int row, int col){
        vector<int> temp = {row, col};
        for(auto v : seen){
            if(v == temp) return true;
        }
        return false;
    }

    int getLowestWall(vector<vector<int>> heightMap, int row, int col){
        vector<vector<int>> points = {{row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};
        int lowest = heightMap[points[0][0]][points[0][1]];
        for(auto v : points){
            if(heightMap[v[0]][v[1]] < lowest) lowest = heightMap[v[0]][v[1]];
        }
        return lowest;
    }

    int computeSum(vector<vector<int>> cells, vector<vector<int>> heightMap){
        int lowest = getLowestWall(heightMap, cells[0][0], cells[0][1]);
        for(auto v : cells){
            int temp = getLowestWall(heightMap, v[0], v[1]);
            if(temp < lowest){
                lowest = temp;
            }
        }
        return cells.size() * lowest;
    }

    public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n = heightMap.size();
        int m = heightMap[0].size();
        vector<vector<int>> seen;
        vector<vector<int>> curr_cells;
        int output = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                bool temp1, temp2;
                temp1 = checkLowest(heightMap, i, j);
                temp2 = checkSecondLowest(heightMap, i, j);
                if(!temp1 && !temp2) {
                    output += computeSum(curr_cells, heightMap);
                    curr_cells.clear();
                    continue;
                }
                if(!seenAlready(seen, i, j)){
                    curr_cells.push_back({i, j});
                }
                seen.push_back({i, j});
            }
        }
        return output;
    }
};


int main(){

    vector<vector<int>> temp = {
        {1, 4, 3, 1, 3, 2},
        {3, 2, 1, 3, 2, 4},
        {2, 3, 3, 2, 3, 1}

    };

    cout << Solution().trapRainWater(temp) << endl;

    return 0;
}