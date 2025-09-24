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

    int comapareVersions(string ver1, string ver2){
        int temp1 = getNumFromString(ver1);
        int temp2 = getNumFromString(ver2);
        if(temp1 == temp2) return 0;
        else if(temp1 < temp2) return -1;
        else return 1;
    }

    public:
    int compareVersion(string version1, string version2) {
        vector<string> temp1 = getSubVersions(version1);
        vector<string> temp2 = getSubVersions(version2);

        int index = 0;
        while(index < temp1.size() && index < temp2.size()){
            int compare = comapareVersions(temp1[index], temp2[index]);
            if(compare != 0) return compare;
            index++;
        }

        while(index < temp1.size()){
            if(getNumFromString(temp1[index]) != 0) return 1;
            index++;
        }

        while(index < temp2.size()){
            if(getNumFromString(temp2[index]) != 0) return -1;
            index++;
        }

        return 0;
    }
};


int main(){

    int output = Solution().compareVersion("1.0.0.10", "1.0.0.0");
    cout << "Output : " << output << endl;

    return 0;
}