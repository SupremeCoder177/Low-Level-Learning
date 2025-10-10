#include <iostream>
#include <set>
#include <vector>


using namespace std;


class Solution {
    public:
    int distributeCandies(int n, int limit) {
        int count = 0;
        if(limit > n) limit = n;
        
        for(int i = 0; i <= limit; i++){
            for(int j = 0; j <= limit; j++){
                for(int k = 0; k <= limit; k++){
                    if(k + i + j == n) count++;
                }
            }
        }
        return count;
    }
};


int main(){

    cout << Solution().distributeCandies(3, 3);

    return 0;
}