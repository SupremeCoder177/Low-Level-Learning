#include <iostream>
#include <stdio.h>
#include <vector>


using namespace std;


class Solution{

    public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        int m = gas.size();
        
        for(int i = 0; i < m; i++){
            int index = i;
            int gas_in_tank = gas[i];
            bool started = false;
            while(true){    
                gas_in_tank -= cost[index];
                if(gas_in_tank <= 0) break;
                index++;
                index %= m;
                started = true;
                gas_in_tank += gas[index];
                if(index == i) break;
            }
            if(index == i && started) return i;
        }   
        return -1;
    }
};


int main(){

    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = { 3, 4, 5, 1, 2};
    cout << Solution().canCompleteCircuit(gas, cost) << endl;

    return 0;
}