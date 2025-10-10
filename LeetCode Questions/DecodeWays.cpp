#include <iostream>
#include <string>
#include <math.h>


using namespace std;


class Solution {

    private:
    void decodeRemaining(string& s, int& ways, int start){
        if(start >= s.size()){
            ways++;
            return;
        }

        if(check_valid(s, start, start)){
            decodeRemaining(s, ways, start + 1);
        }
        if(check_valid(s, start, start + 1)){
            decodeRemaining(s, ways, start + 2);
        }
    }

    bool check_valid(string& s, int start, int end){
        if(end >= s.size()) return false;
        if(s[start] == '0') return false;

        string temp;
        for(int i = start; i <= end; i++){
            temp += s[i];
        }
        int num = stoi(temp);
        
        return (1 <= num) && (num <= 26);
    }

    public:
    int numDecodings(string s) {
        int count = 0;
        decodeRemaining(s, count, 0);
        return count;
    }
};


int main(){

    cout << Solution().numDecodings("12") << endl;

    return 0;
}