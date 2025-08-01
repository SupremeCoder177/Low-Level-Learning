#include <stdio.h>

int main(){

    int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    int* num = nums; // num points to the memory address of nums[0] and hence num == &nums[0]
    printf("Num = %d\n", *num);
    if(num == &nums[0]){
        printf("Hypothesis was correct indeed .\n");
    }else{
        printf("Okay maybe I need to study pointers a little more.\n");
    }

    return 0;
}