#include <vector>
#include <iostream>


using namespace std;


class Solution{

    public:
    int pivotInteger(int n){
        
        vector<int> temp(n, 0);

        for(int i = 1; i <= n; i++){
            temp[i - 1] = i;
        }

        for(int i = 1; i < n; i++){
            temp[i] += temp[i - 1];
        }

        for(int i = 0; i < n; i++){
            if(temp[i] == temp[n - 1] - temp[i] + i + 1) return i + 1;
        }

        return -1;
    }
};


int main(){

    cout << Solution().pivotInteger(4) << endl;

    return 0;
}