#include <stdio.h>
#include <stdlib.h>

int main(){

    //Stack variables
    int num = 10;
    int nums[] = {1, 2, 3, 4};

    //Heap Variables
    int* hNum = (int*)malloc(sizeof(int));
    int* hNums = (int*)calloc(4, sizeof(int));

    printf("Stack variables :\n");
    printf("%d\n", num);
    for(size_t i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i){
        printf("%d\n", nums[i]);
    }

    //Printing the values of heap variables will always
    //result in a random number because we didn't set it

    //whereas hNums will all be initialized to 0 because of calloc

    printf("\n");
    printf("Heap variables:\n");
    printf("%d\n", *hNum);
    for(size_t i = 0; i < 4; ++i){
        printf("%d\n", hNums[i]);
    }

    //always remember to free memory after using variables
    free(hNum);
    free(hNums);

    return 0;
}