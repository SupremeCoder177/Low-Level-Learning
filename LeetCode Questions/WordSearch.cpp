#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Solution {
    private:
    bool search(string word, vector<vector<char>>& board, int row, int col, vector<vector<bool>> seen, int n, int m){
        if(word.empty()) return true;
        for(auto v : get_valid_adjacents(row, col, n, m)){
            if(board[v[0]][v[1]] == word[0] && !seen[v[0]][v[1]]){
                seen[v[0]][v[1]] = true;
                if(search(removeAndReturn(word), board, v[0], v[1], seen, n, m)) return true;
            }
        }
        return false;
    }

    string removeAndReturn(string s){
        s.erase(s.begin());
        return s;
    }

    vector<vector<int>> get_valid_adjacents(int row, int col, int n, int m){
        vector<vector<int>> out;
        for(auto v : get_surrounding(row, col)){
            if(v[0] >= 0 && v[0] < n && v[1] >= 0 && v[1] < m) out.push_back(v);
        }
        return out;
    }

    vector<vector<int>> get_surrounding(int row, int col){
        return {{row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};
    }

    public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>> seen(n, vector<bool>(m, false));

        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if(board[i][j] == word[0]){
                    seen[i][j] = true;
                    if(search(removeAndReturn(word), board, i, j, seen, n, m)) return true;
                    else{
                        seen.assign(n, vector<bool>(m, false));
                    }
                }
            }
        }
        return false;
    }
};


int main(){

    vector<vector<char>> temp = {
        {'a', 'b', 'c', 'e'},
        {'s', 'f', 'c', 's'},
        {'a', 'd', 'e', 'e'}
};

    cout << boolalpha;
    cout << Solution().exist(temp, "abcb");

    return 0;
}