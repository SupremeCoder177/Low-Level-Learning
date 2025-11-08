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

    string substring(string s, int index1, int index2){
        string out;
        for(int i = index1; i < index2; i++){
            out += s[i];
        }
        return out;
    }

    bool isValid(string s){
        if(s.size() > 1 && s[0] == '0') return false;
        return strti(s) >= 0 && strti(s) <= 255;
    }

    public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> out;

        int n = s.size();
        if(n < 4 || n > 12) return out;
        
        for(int i = 2; i >= 0; i--){
            if(i + 3 >= n) continue;
            for(int j = i + 3; j > i; j--){
                if(j >= n) continue;
                for(int k = j + 3; k > j; k--){
                    if(k >= n) continue;
                    for(int l = k + 3; l > k; l--){
                        if(l >= n) continue;
                        if(l + 1 < n) break;
                        string temp1 = substring(s, 0, i + 1);
                        if(!isValid(temp1)) continue;
                        string temp2 = substring(s, i + 1, j + 1);
                        if(!isValid(temp2)) continue;
                        string temp3 = substring(s, j + 1, k + 1);
                        if(!isValid(temp3)) continue;
                        string temp4 = substring(s, k + 1, l + 1);
                        if(!isValid(temp4)) continue;
                        out.push_back(temp1 + "." + temp2 + "." + temp3 + "." + temp4);
                    }
                }
            }
        }

        return out;
    }
};


int main(){

    for(auto s : Solution().restoreIpAddresses("0000")){
        cout << s << " ";
    }
    cout << endl;

    return 0;
}