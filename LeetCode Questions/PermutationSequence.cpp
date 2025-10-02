#include <iostream>
#include <vector>
#include <string>


using namespace std;


class Solution {

    private:
    void recursiveAdd(vector<string>& in, vector<string> array){
        if(array.empty()) return;
        vector<string> copy = in;
        in.clear();
        vector<string> temp;
        for(string s : copy){
            for(int i = 0; i < array.size(); i++){
                string holder = s + array[i];
                temp.push_back(holder);
                recursiveAdd(temp, removeIndex(array, i));
                for(string ch : temp) in.push_back(ch);
                temp.clear();
            }
        }
    }

    string getString(int num){
        string out = "";
        int exp {1};
        while(num / exp >= 10){
            exp *= 10;
        }
        while(exp > 0){
            out += (char)((num / exp) % 10 + (int) '0');
            exp /= 10;
        }
        return out;
    }

    vector<string> removeIndex(vector<string> arr, int index){
        arr.erase(arr.begin() + index);
        return arr;
    }

    public:
    string getPermutation(int n, int k) {
        vector<string> permuatations;
        vector<string> arr;

        for(int i = 1; i <= n; i++) arr.push_back(getString(i));

        for(int i = 0; i < n; i++){
            vector<string> temp = {{arr[i]}};
            recursiveAdd(temp, removeIndex(arr, i));
            for(auto v : temp) permuatations.push_back(v);
        }
        return permuatations[k - 1];
    }
};


int main(){

    cout << Solution().getPermutation(3, 3) << endl;

    return 0;
}