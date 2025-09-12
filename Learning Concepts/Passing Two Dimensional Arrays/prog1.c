#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print(char* str){
    size_t len = strlen(str);
    for(size_t i = 0; i < len; i++){
        printf("%c", str[i]);
    }
    printf("\n");
}


void printArr(int* arr, int size, int col_length){
    for(size_t i = 0; i < size * col_length; i++){
        printf("%d ", arr[i]);
        if((i + 1) % col_length == 0) printf("\n");
    }
}


int main(){

    print("Hello there !");
    srand(time(NULL));

    int array[10][10];
    for(size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++){
        for(size_t j = 0; j < sizeof(array[0]) / sizeof(int); j++){
            array[i][j] = rand() % 10 + 1;
        }
    }

    printArr(array[0], sizeof(array) / sizeof(array[0]), sizeof(array[0]) / sizeof(int));

    return 0;
}