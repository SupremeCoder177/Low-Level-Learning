#include <stdio.h>

int main(int argc, char* argv[]){

    //opening a file in write mode
    FILE* dummy = fopen("dummy.txt", "w");

    //writing  to the file
    fputs("Hello there is a test to write dummy data to the dummy.txt file.", dummy);

    //flushing data from the buffer 
    fflush(dummy);

    //closing the file
    fclose(dummy);

    return 0;
}