#include <iostream>
#include <math.h>
#include <queue>
#include <vector>


using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};


class Solution {
    public:

    int minDepth(TreeNode* root){
        if(root == nullptr) return 0;

        int depth = 0;
        queue<TreeNode*> nodes;
        nodes.push(root);

        while(!nodes.empty()){
            vector<TreeNode*> temp;
            depth++;
            while(!nodes.empty()){
                TreeNode* node = nodes.front();
                if(node->left == nullptr && node->right == nullptr && node != root) return depth;
                if(node->left != nullptr) temp.push_back(node->left);
                if(node->right != nullptr) temp.push_back(node->right);
                nodes.pop();
            }
            for(auto v : temp) nodes.push(v);
        }
        return depth;
    }
};


int main(){

    TreeNode a = TreeNode(7);
    TreeNode b = TreeNode(15);
    TreeNode c = TreeNode(20, &b, &a);
    TreeNode d = TreeNode(9);
    TreeNode e = TreeNode(3, &d, &c);

    cout << Solution().minDepth(&e) << endl;

    return 0;
}