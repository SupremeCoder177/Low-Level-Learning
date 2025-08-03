#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

    //opening a file passed in to the CL 
    // arguments and printing their contents on the console
    FILE* temp;

    for(size_t i = 0; i < argc; ++i){
        temp = fopen(argv[i], "r");
        //checking if the file exists
        if(temp){
            printf("Printing contents of %s\n", argv[i]);
            char buf[100];
            while(1){
                if(fgets(buf, sizeof(buf), temp) == NULL){
                    fprintf(stderr, "EOF reached/an error has occured .\n");
                    break;
                }else{
                    printf("%s\n", buf);
                }
            }
            fclose(temp);
        }
    }

    return 0;
}