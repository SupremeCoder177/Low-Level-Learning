#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {

        int area1 = (ax2 - ax1) * (ay2 - ay1);
        int area2 = (bx2 - bx1) * (by2 - by1);
        int common_width = max(0, min(ax2, bx2) - max(ax1, bx1));
        int common_height = max(0, min(ay2, by2) - max(ay1, by1));
        
        int common_area = common_width * common_height;

        return area1 + area2 - common_area;
    }
};


int main(){

    cout << Solution().computeArea(-2, -2, 2, 2, -3, -3, 3, -1) << endl;

    return 0;
}