// Let's explain each step

// This is how you import code into you file
#include <stdio.h>

/* The file that you run must have a function called main because it gets called when the file is run
   argc and argv are variables for holding input passed into the file before running it
   argc represents the number of arguments
   argv is the pointer pointing to the list of arguments passed into the file 
    though they are unnecessary here
*/

int main(int argc, char* argv[]){
    printf("Hello world !");
    return 0;
}