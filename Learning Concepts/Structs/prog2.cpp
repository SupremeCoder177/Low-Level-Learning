#include <iostream>


using namespace std;

// of course that means that there are 
// structs in C++

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int main(){

    TreeNode t = TreeNode(10);
    cout << t.val << endl;

    return 0;
}