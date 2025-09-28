#include <iostream>
#include <vector>


using namespace std;


class Solution {

    private:

    int get_number(char ch){
        return (int) ch - (int) '0';
    }

    vector<int> get_numbers_in_block(vector<vector<char>> board, int x, int y){
        int block_x = (int)(x / 3) * 3;
        int block_y = (int)(y / 3) * 3;
        vector<int> output;
        for(int i = block_y; i < block_y + 3; i++){
            for(int j = block_x; j < block_x + 3; j++){
                output.push_back(get_number(board[i][j]));
            }
        }
        return output;
    }

    vector<int> get_numbers_in_row(vector<vector<char>> board, int y){
        vector<int> output;
        for(int i = 0; i < 9; i++){
            output.push_back(get_number(board[y][i]));
        }
        return output;
    }

    vector<int> get_number_in_column(vector<vector<char>> board, int x){
        vector<int> output;
        for(int i = 0; i < 9; i++){
            output.push_back(get_number(board[i][x]));
        }
        return output;
    }

    int choose_number(int x, int y, vector<vector<char>> board){
        vector<int> nums_in_block = get_numbers_in_block(board, x, y);
        vector<int> nums_in_row = get_numbers_in_row(board, y);
        vector<int> nums_in_col = get_number_in_column(board, x);

        for(int i = 0; i < 9; i++){
            bool temp = true;
            for(int j : nums_in_block){
                if(j == i){
                    temp = false;
                    break;
                }
            }
            if(!temp) continue;
            temp = true;
            for(int j : nums_in_row){
                if(j == i){
                    temp = false;
                    break;
                }
            }
            if(!temp) continue;
            temp = true;
            for(int j : nums_in_col){
                if(j == i){
                    temp = false;
                    break;
                }
            }
            if(!temp) continue;
            return i;
        }
        return -1;
    }

    bool fill(vector<vector<char>>& board){
        int temp;
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                temp = choose_number(j, i, board);
                if(temp < 0){
                    break;
                }
                board[i][j] = (char)(temp + (int) '0');
            }
            if(temp < 0) break;
        }
        if(temp < 0) return false;
        else return true;
    }

    public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<vector<char>> copy = board;
        while(true){
            if(fill(board)) break;
            else board = copy;
        }
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