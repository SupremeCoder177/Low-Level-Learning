#include <iostream>
#include <vector>
#include <string>


using namespace std;


class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int count = 0;

        int m = bank.size();
        int n = bank[0].size();

        vector<int> lasers;
        
        for(int i = 0; i < m; i++){
            int temp = 0;
            for(int j = 0; j < n; j++){
                if(bank[i][j] == '1') temp++;
            }
            lasers.push_back(temp);
        }

        for(int i = 0; i < m; i++){
            if(lasers[i] > 0 && i < m - 1){
                for(int j = i + 1; j < m; j++){
                    if(lasers[j] > 0){ 
                        count += lasers[i] * lasers[j];
                        break;
                    }
                }
            }
        }

        return count;
    }
};
 

int main(){

    vector<string> temp = {
        "011001",
        "000000",
        "010100",
        "001000"
    };

    cout << Solution().numberOfBeams(temp) << endl;

    return 0;
}