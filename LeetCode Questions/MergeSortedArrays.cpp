#include <iostream>
#include <vector>


using namespace std;


class Solution {
    public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> temp;
        int l = 0, r = 0;
        while(l < m && r < n){
            if(nums1[l] < nums2[r]){
                temp.push_back(nums1[l]);
                l++;
            }
            else{
                temp.push_back(nums2[r]);
                r++;
            }
        }

        while(l < m){
            temp.push_back(nums1[l]);
            l++;
        }
        while(r < n){
            temp.push_back(nums2[r]);
            r++;
        }
        nums1 = temp;
    }
};


int main(){

    vector<int> temp = {1, 2, 3, 0, 0};
    vector<int> temp2 = {2, 5, 6};
    Solution().merge(temp, 3, temp2, temp2.size());

    for(int i : temp) cout << i << " ";
    cout << endl;

    return 0;
}