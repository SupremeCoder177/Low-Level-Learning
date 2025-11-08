#include <iostream>
#include <math.h>

using namespace std;

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode() : left(nullptr), right(nullptr), val(0) {}
    TreeNode(int x): left(nullptr), right(nullptr), val(x) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : left(left), right(right), val(x) {}
};


class Solution {

    private:
    bool isValidLeftNode(TreeNode* node, int upper){
        if(node == nullptr) return true;
        else if(node->left == nullptr && node->right == nullptr) return true;
        else{
            if(node->left != nullptr && node->val <= node->left->val) return false;
            if(node->right != nullptr && node->val >= node->right->val) return false;

            if(node->left != nullptr && node->left->val >= upper) return false;
            if(node->right != nullptr && node->right->val >= upper) return false;
        
            return isValidLeftNode(node->left, node->val) && isValidRightNode(node->right, node->val);
        }
    }

    bool isValidRightNode(TreeNode* node, int lower){
        if(node == nullptr) return true;
        else if(node->left == nullptr && node->right == nullptr) return true;
        else{
            if(node->left != nullptr && node->val <= node->left->val) return false;
            if(node->right != nullptr && node->val >= node->right->val) return false;

            if(node->left != nullptr && node->left->val <= lower) return false;
            if(node->right != nullptr && node->right->val <= lower) return false;

            return isValidLeftNode(node->left, node->val) && isValidRightNode(node->right, node->val);
        }
    }

    public:
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) return true;
        if(root->left != nullptr && root->val <= root->left->val) return false;
        if(root->right != nullptr && root->val >= root->right->val) return false;
        return isValidLeftNode(root->left, root->val) && isValidRightNode(root->right, root->val);
    }
};


int main(){

    TreeNode a = TreeNode(1);
    TreeNode b = TreeNode(3);
    TreeNode c = TreeNode(2, &a, &b);
    TreeNode d = TreeNode(4);
    TreeNode e = TreeNode(5, &d, &c);

    cout << boolalpha;
    cout << "Is valid tree : " << Solution().isValidBST(&c) << endl;

    return 0;
}