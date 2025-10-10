#include <iostream>
#include <string>


using namespace std;


class Solution {
    public:
    bool hasSameDigits(string s) {
        string temp;
        while(s.size() != 2){
            temp.clear(); 
            int n = s.size();

            for(int i = 0; i < n - 1; i++){
                int p1 = ((int)(s[i] - '0') + (int)(s[i + 1] - '0')) % 10;
                temp += '0' + p1;
            }
            s = temp;
        }
        return s[0] == s[1];
    }
};


int main(){

    cout << boolalpha;
    cout << Solution().hasSameDigits("3902") << endl;
    
    return 0;
}