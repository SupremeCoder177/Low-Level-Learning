#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


class Solution {
    public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int n = arr.size();
        int d = arr[1] - arr[0];
        bool acend = true;
        for(int i = 1; i < n; i++){
            if(arr[i] - arr[i - 1] != d) {
                acend = false;
                break;
            }
        }

        if(acend) return true;
        d = arr[0] - arr[1];
        for(int i = n - 2; i >= 0; i--){
            if(arr[i] - arr[i + 1] != d) return false;
        }
        return true;
    }
};


int main(){

    vector<int> temp = {4, 2, 1};

    cout << boolalpha;
    cout << Solution().canMakeArithmeticProgression(temp) << endl;

    return 0;
}