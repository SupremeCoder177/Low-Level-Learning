#include <iostream>
#include <queue>


using namespace std;


struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Solution {

    private:

    vector<TreeNode*> traverseNodes(vector<TreeNode*> in){
        vector<TreeNode*> out;
        for(auto node : in){
            if(node->left != nullptr) out.push_back(node->left);
            if(node->right != nullptr) out.push_back(node->right);
        }
        return out;
    }

    public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int out = 0;
        vector<TreeNode*> temp = {root};

        while(!temp.empty()){
            temp = traverseNodes(temp);
            out++;
        }
        return out;
    }
};


int main(){

    TreeNode a = TreeNode(15);
    TreeNode b = TreeNode(7);
    TreeNode c = TreeNode(20, &a, &b);
    TreeNode d = TreeNode(9);
    TreeNode e = TreeNode(3, &d, &c);

    cout << Solution().maxDepth(&e) << endl;

    return 0;
}