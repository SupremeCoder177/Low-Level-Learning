#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:

    int get_number(char ch){
        return (int) ch - (int) '0';
    }

    char get_char(int x){
        return (char)( x + '0');
    }

    vector<int> get_numbers_in_block(vector<vector<char>>& board, int x, int y){
        int block_x = (int)(x / 3) * 3;
        int block_y = (int)(y / 3) * 3;
        vector<int> output;
        for(int i = block_y; i < block_y + 3; i++){
            for(int j = block_x; j < block_x + 3; j++){
                if(board[i][j] != '.') output.push_back(get_number(board[i][j]));
            }
        }
        return output;
    }

    vector<int> get_numbers_in_row(vector<vector<char>>& board, int y){
        vector<int> output;
        for(int i = 0; i < 9; i++){
            if(board[y][i] != '.') output.push_back(get_number(board[y][i]));
        }
        return output;
    }

    vector<int> get_number_in_column(vector<vector<char>>& board, int x){
        vector<int> output;
        for(int i = 0; i < 9; i++){
            if(board[i][x] != '.') output.push_back(get_number(board[i][x]));
        }
        return output;
    }

    pair<int, int> find_first_empty(vector<vector<char>> board){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.'){
                    return pair<int, int>{i, j};
                }
            }
        }
        return pair<int, int>{-1, -1};
    }

    bool fill(vector<vector<char>>& board){
        pair<int, int> temp = find_first_empty(board);
        if(temp.first < 0) return true;

        int x = temp.second;
        int y = temp.first;
        
        vector<int> available;
        vector<int> in_row = get_numbers_in_row(board, y);
        vector<int> in_column = get_number_in_column(board, x);
        vector<int> in_block = get_numbers_in_block(board, x, y);

        for(int i = 1; i <= 9; i++){
            bool valid = true;
            for(int j : in_row) {if(i == j) valid = false; break;}
            if(!valid) continue;
            for(int j : in_column) {if(i == j) valid = false; break;}
            if(!valid) continue;
            for(int j : in_block) {if(i == j) valid = false; break;}
            if(!valid) continue;
            if(valid) available.push_back(i);
        }
        if(available.empty()) return false;

        for(int i : available){
            board[temp.first][temp.second] = get_char(i);
            if(fill(board)) return true;
            board[temp.first][temp.second] = '.';
        }
        return false;
    }

    public:
    void solveSudoku(vector<vector<char>>& board) {
        fill(board);
    }
};


int main(){

    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    Solution().solveSudoku(board);

    for(auto v : board){
        for(char c : v){
            cout << c << " ";
        }
        cout << endl;
    }

    return 0;
}