#include <stdio.h>
#include <string.h>

//Sometimes taking in put from scanf can overwrite over other variables

int main(){

    char input[10];
    char temp[] = "AAAAAAAAA";
    printf("Enter:\n");
    scanf("%s", input); // if user enter more than 10 characters and temp is adjacent to input1 on stack, it will overwrite temp
                        // or it will cause undefined behaviour because input is only allocated 10 bytes, but if we enter 
                        // more than 10 bytes in scanf, it will overwrite beyond its bounds, and cause the program to crash
    
    printf("input1 : %s\n", input);
    printf("temp : %s\n", temp);

    return 0;
}