#include <iostream>
#include <vector>


using namespace std;


struct ListNode{
    ListNode* next;
    int val;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
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
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode* root = new TreeNode(head->val);
        vector<TreeNode*> temp = {root};
        ListNode* curr_node = head->next;

        int index = 0;
        int left = true;

        while(curr_node != nullptr){
            TreeNode* temp_node = new TreeNode(curr_node->val);
            if(left){
                temp[index]->left = temp_node;
            }else{
                temp[index]->right = temp_node;
            }
            
            index++;
            if(index >= temp.size()){
                if(left){
                    left = false;
                }else{
                    temp = traverseNodes(temp);
                    index = 0;
                    left = true;
                }
            }

            curr_node = curr_node->next;
        }

        return root;
    }
};


int main(){

    ListNode a = ListNode(9);
    ListNode b = ListNode(5, &a);
    ListNode c = ListNode(0, &b);
    ListNode d = ListNode(-3, &c);
    ListNode e = ListNode(-10, &d);

    TreeNode* temp = Solution().sortedListToBST(&e);

    cout << temp->val << endl;

    delete temp;

    return 0;
}