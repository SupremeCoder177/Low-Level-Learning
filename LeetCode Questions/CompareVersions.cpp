#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;


class Solution {

    private:
    int getNumFromString(string s){
        int output = 0;
        for(int i = 0; i < s.length(); i++){
            output += pow(10, s.length() - (i + 1)) * ((int) s[i] - (int) '0');
        }
        return output;
    }

    vector<string> getSubVersions(string s){
        vector<string> temp;
        string sub_ver = "";

        for(int i = 0; i < s.length(); i++){
            if(s[i] != '.') sub_ver += s[i];
            if(s[i] == '.' || i == s.length() - 1){
                temp.push_back(sub_ver);
                sub_ver = "";
            }
        }
        return temp;
    }

    public:
    int compareVersion(string version1, string version2) {
        vector<string> temp1 = getSubVersions(version1);
        vector<string> temp2 = getSubVersions(version2);

        int ver1, ver2;
        int i = 0;
        while(i < temp1.size() && i < temp2.size()){
            if(getNumFromString(temp1[i]) < getNumFromString(temp2[i])) return -1;
            else if(getNumFromString(temp1[i]) > getNumFromString(temp2[i])) return 1;
            i++;
        }
        if(i < temp1.size()) return 1;
        else if(i < temp2.size()) return -1;
        return 0;
    }
};


int main(){

    int output = Solution().compareVersion("1.0.0.10", "1.0.0.0");
    cout << "Output : " << output << endl;

    return 0;
}