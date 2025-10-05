#include <iostream>

using namespace std;


class Solution {

    private:
    void add_nodes(int node_remaining, int& count){
        if(node_remaining == 0){
            count++;
            return;
        }
        add_nodes(node_remaining - 1, count);
        if(node_remaining - 2 >= 0) add_nodes(node_remaining - 2, count);
    }

    public:
    int numTrees(int n) {
        int out = 0;
        add_nodes(n, out);
        return (out * 2) - 1;
    }
};


int main(){

    cout << Solution().numTrees(3) << endl;

    return 0;
}