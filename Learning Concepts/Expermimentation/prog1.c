#include <stdio.h>

// I wanted to see what exactly gets passed in the argc and argv values 
int main(int argc, char* argv[]){
    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    return 0;
}