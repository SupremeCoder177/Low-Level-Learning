#include <stdio.h>
#include <stdlib.h>

int main(){

    // now using malloc to initialize an array of 10 integers
    int* nums = (int*) malloc(sizeof(int) * 10);

    //printing the values at nums
    printf("Malloc memory allocation:\n");
    for(int i = 0; i < 10; i++){
        printf("%d\n", nums[i]);
    }

    free(nums);

    //Using calloc to initialize an array of 10 integers
    nums = (int*) calloc(10, sizeof(int));

    //printing the values at nums
    printf("Calloc memory allocation:\n");
    for(int i = 0; i < 10; i++){
        printf("%d\n", nums[i]);
    }

    // Let's now realloc the size of nums using realloc
    nums = (int*) realloc(nums, 11 * sizeof(int));

    printf("Printing after reallocation:\n");
    for(int i = 0; i < 11; i++){
        printf("%d\n", nums[i]);
    }

    //we will see that the last value in nums is some garbage value
    //this shows that the memory was reallocted

    free(nums);

    return 0;
}