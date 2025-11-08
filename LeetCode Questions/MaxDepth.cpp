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
    public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int out = 1;

        queue<TreeNode*> temp;
        temp.push(root);
        int this_layer_nodes_count = 1;
        int next_layer_nodes = 0;
        
        while(!temp.empty()){
            TreeNode* curr_node = temp.front();
            temp.pop();
            this_layer_nodes_count -= 1;
            if(curr_node->left != nullptr) {temp.push(curr_node->left); next_layer_nodes++;}
            if(curr_node->right != nullptr) {temp.push(curr_node->right); next_layer_nodes++;}

            if(this_layer_nodes_count == 0 && next_layer_nodes > 0){
                out++;
                this_layer_nodes_count = next_layer_nodes;
                next_layer_nodes = 0;
            }
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