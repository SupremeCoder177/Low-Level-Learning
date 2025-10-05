#include <iostream>
#include <string>


using namespace std;


class Solution {
    public:
    bool isPalindrome(string s) {
        string temp;
        for(int i = 0; i < s.size(); i++){
            if(isalnum(s[i])) temp.push_back(tolower(s[i]));
        }

        cout << temp << endl;
        int n = temp.size();
        for(int i = 0; i < n; i++){
            if(temp[i] != temp[n - (i + 1)]) return false;
        }
        return true;
    }
};


int main(){

    cout << boolalpha;
    cout << Solution().isPalindrome("A man, a plan, a canal: Panama") << endl;

    return 0;
}