#include <stdio.h>


// Experimenting with double pointers and so on
int main(){

    int orginal_num = 7;
    int* num1 = &orginal_num; // each pointer hold an address, & returns the address of any variable
    int** num2 = &num1;  
    int*** num3 = &num2;
    // int num4 = num3;  this is illgal because the data in num3 sure is an address which at the end of the day is a number, but C 
    //                   sees it as an int*** type, and also the type of the memory address of num3 is int****

    printf("%d\n", orginal_num);
    printf("%d\n", *num1);
    printf("%d\n", **num2);
    printf("%d\n", ***num3);
    // printf("%d\n", num4);

    return 0;
}