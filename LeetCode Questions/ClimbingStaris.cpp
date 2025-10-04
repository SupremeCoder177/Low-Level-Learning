#include <iostream>

class Solution {

    private:
    void climb(int remaining, int& count){
        if(remaining <= 0) {
            if(remaining == 0) count++;
            return;
        }
        climb(remaining - 1, count);
        climb(remaining - 2, count);
    }

    public:
    int climbStairs(int n) {
        int count = 0;
        climb(n, count);
        return count;
    }
};

int main(){

    std::cout << Solution().climbStairs(2) << std::endl;

    return 0;
}