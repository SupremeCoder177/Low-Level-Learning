#include <stdio.h>
#include <string.h>

int main(){

    const char* names[] = {"John Doe", "Mark Manson", "Tony Stark"}; 
    //This is interesting
    // names in this case is not an array of strings
    // it is an array of char*
    // and each char* corresponds to each element written in the array
    
    int name1 = strlen(names[0]);
    int name2 = strlen(names[1]);
    int name3 = strlen(names[2]);
    // strlen returns the length of a string by iterating over a char* until it hits a \0 character 
    // every string ends with an escape character \0

    printf("%d %d %d", name1, name2, name3);

    return 0;
}