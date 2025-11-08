#include <iostream>
#include <vector>
#include <string>
#include <math.h>


using namespace std;


class Solution {

    private:
    int strti(string in){
        int out = 0;
        int n = in.size();
        for(int i = 0; i < n; i++){
            out += pow(10, n - (i + 1)) * ((int) in[i] - (int) '0');
        }
        return out;
    }


    public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> out;
        
        cout << strti("100");

        return out;
    }
};


int main(){

    for(auto s : Solution().restoreIpAddresses("25525511135")){
        cout << s << " ";
    }
    cout << endl;


    return 0;
}