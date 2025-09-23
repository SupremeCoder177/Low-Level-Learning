#include <iostream>
#include <limits>
#include <math.h>

class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 0) return 0;

        bool negative = false;
        if(dividend < 0 && divisor > 0) negative = true;
        if(divisor < 0 && dividend > 0) negative = true;


        if(abs((long long) divisor) == 1){
            if(negative){
                if(dividend < 0) return dividend;
                else return -dividend;
            }
            else{
                if(dividend < 0) {
                    if(dividend > std::numeric_limits<int>::min()){
                        return -dividend;
                    }else{
                        return std::numeric_limits<int>::max();
                    }
                }
                    
                else return dividend;
            }
        }

        long long temp = 0;
        long long target = abs((long long) dividend);
        long long div = abs((long long) divisor);
        std::cout << target << std::endl;
        int output = 0;
        while(temp <= target){
            temp += div;
            if(temp > target) {
                std::cout << "returning" << std::endl;
                return negative ? -output : output;
            }
            output++;
        }
        if(temp == target && target > std::numeric_limits<int>::max() && dividend < 0) return negative ? -(output - 1) : output - 1;
        return negative ? -output : output;
    }
};

int main(){

    std::cout << Solution().divide(-2147483648, 2) << std::endl;

    return 0;
}