#include <stdio.h>
#include <stdlib.h>



// this is how you define a struct in C
// C doesn't have any OOP, so the closest thing to objects in C
// is just structs, they have properties 
// like variables you can instantite variables of type of your struct and set or access those properties
typedef struct Human{
    char* name;
    int age;
} Human;


int main(int argc, char* argv[]){

    // for fun
    for(size_t i = 0; i < argc; ++i){
        printf("%s\n", argv[i]);
    }

    struct Human h1; 
    h1.name = "John Doe";
    h1.age = 20;

    return 0;
}