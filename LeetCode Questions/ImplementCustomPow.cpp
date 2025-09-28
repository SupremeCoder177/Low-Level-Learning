#include <iostream>


class Solution {
public:
    double myPow(double x, double n) {
        if(n == 0) return 1;
        if(n < 0) return 1 / myPow(x, -n);
        if(n == 1) return x;

        double half = myPow(x, n / 2);
        if((long long) n % 2 == 0){
            return half * half;
        }else{
            return half * half * x;
        }
    }
};


int main(){

    std::cout << "Pow(2, 10) : " << Solution().myPow(2, -10) << std::endl;

    return 0;
}