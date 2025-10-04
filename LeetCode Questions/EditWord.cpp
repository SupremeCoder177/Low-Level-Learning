#include <iostream>
#include <string>


using namespace std;


class Solution {

    public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();
        int steps = 0;
        int same = 0;

        int ptr1 = 0, ptr2 = 0;

        while(ptr1 < len1 && ptr2 < len2){
            if(!(word1[ptr1] == word2[ptr2])){
                steps++;
            }else{
                same++;
            }
            ptr1++;
            ptr2++;
        }
        if(same != len2){
            steps += len2 - same;
        }
        return steps;
    }
};


int main(){

    cout << Solution().minDistance("horse", "ros") << endl;

    return 0;
}