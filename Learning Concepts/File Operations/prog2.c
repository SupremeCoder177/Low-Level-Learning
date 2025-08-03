#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

    //opening every single file passed
    //into the CL arguments in append mode
    FILE* temp;
    
    for(size_t i = 0; i < argc; ++i){
        temp = fopen(argv[i], "a");
        fputs("This file was altered by prog2.c\n", temp);

        //closing a file automatically flushes the buffer 
        fclose(temp);
    }

}