#include <iostream>
#include <stdio.h>
#include <vector>


using namespace std;


class Solution{

    public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        int m = gas.size();
        
        for(int i = 0; i < m; i++){
            int gas_in_tank = gas[i];
            bool started = false;
            int index = i;
            index %= m;
            while(true){
                gas_in_tank -= cost[index];
                index++;
                index %= m;
                if(gas_in_tank <= 0) break;
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

    vector<int> gas = {4, 5, 3, 1, 4};
    vector<int> cost = { 5, 4, 3, 4, 2};
    cout << Solution().canCompleteCircuit(gas, cost) << endl;

    return 0;
}