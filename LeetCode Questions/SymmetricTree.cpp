#include <iostream>
#include <vector>
#include <queue>

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {};
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {};
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


using namespace std;


class Solution{

    public:
    bool isSymmetric(TreeNode* root){
        vector<int> nodes;
        TreeNode* temp, left, right;
        queue<TreeNode*> waiting;
        waiting.push(root);

        while(!waiting.empty()){
            temp = waiting.front();
            left = *temp->left;
            right = *temp->right;
            waiting.pop();
            
            waiting.push(&left);
            waiting.push(&right);
            nodes.push_back(temp->val);
        }

        return false;
    }
};

int main(){

    TreeNode a(3);
    TreeNode b(4);
    TreeNode c(2, &b, &a);
    TreeNode d(4);
    TreeNode e(3);
    TreeNode f(2, &e, &d);
    TreeNode g(1, &f, &c);

    cout << Solution().isSymmetric(&g) << endl;

    return 0;
}