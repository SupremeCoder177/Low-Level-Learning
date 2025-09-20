#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


class Solution {

    private:
    map<string, int> map_items(vector<string> words){
        map<string, int> output;
        for(string word : words){
            if(output.find(word) != output.end()){
                output[word]++;
            }else{
                output[word] = 1;
            }
        }
        return output;
    }

    public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int check_length = words[0].length() * words.size();
        vector<int> output;
        int n = s.length();
        if(n < check_length) return output;

        int left_ptr = 0;
        int delta = words[0].length();
        int total_words = words.size();
        map<string, int> temp;
        map<string, int> words_mapping = map_items(words);

        while(left_ptr < n - check_length){
            temp.clear();
            for(int i = left_ptr; i <= left_ptr + check_length; i += delta){
                string sub = s.substr(i, delta);
                temp[sub]++;
            }

            if(temp == words_mapping) output.push_back(left_ptr);

            left_ptr += 1;
        }
        return output;
    }
};


int main(){

    vector<string> temp = {{"foo", "bar"}};
    string s = "barfoothefoobarman";
    string tmp = s.substr(0, 4);

    cout << tmp << endl;
    
    //for(int i : Solution().findSubstring(s, temp)) cout << i << endl;
    
    return 0;
}