#include <iostream>
#include <vector>

using namespace std;


struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


class Solution {

    private:
    vector<int> traverseNodes(ListNode* head){
        vector<int> out;
        ListNode* curr_node = head;
        while(curr_node != nullptr){
            out.push_back(curr_node->val);
            curr_node = curr_node->next;
        }
        return out;
    }

    public:
    ListNode* partition(ListNode* head, int x) {
        vector<int> listView = traverseNodes(head);
        vector<int> temp;

        for(int i : listView){
            if(i < x) temp.push_back(i);
        }
        for(int i : listView){
            if(i >= x) temp.push_back(i);
        }

        ListNode* curr_node = head;
        int i = 0;
        while(curr_node != nullptr){
            curr_node->val = temp[i];
            i++;
            curr_node = curr_node->next;
        }
        return head;
    }
};


int main(){

    ListNode f = ListNode(2);
    ListNode e = ListNode(5, &f);
    ListNode d = ListNode(2, &e);
    ListNode c = ListNode(3, &d);
    ListNode a = ListNode(4, &c);
    ListNode b = ListNode(1, &a);

    ListNode* head = Solution().partition(&b, 3);

    while(head != nullptr){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;

    return 0;
}