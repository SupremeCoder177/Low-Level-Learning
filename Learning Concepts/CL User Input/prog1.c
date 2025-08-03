#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

void print(const char* string){
    size_t len = strlen(string);
    for(size_t i = 0; i < len; ++i){
        putchar(string[i]);
    }
    putchar('\n');
}

//probably the easiest thing to learn is to how to get string input


// fgets reads from the a FILE stream, which can be stdin, fopen() object and so on
char* get_string(const char* prompt, size_t max_len){
    char* buf = (char*)calloc(max_len, sizeof(char));
    while(1){
        printf("%s\n", prompt);
        if(fgets(buf, max_len, stdin) == NULL){
            fprintf(stderr, "Invalid input !!\n");
            continue;
        }
        if(*buf == '\n'){
            print("Please enter something !");
            continue;
        }
        return buf;
    }
}

int get_int(const char* prompt, size_t limit){
    char* buf = (char*)calloc(limit, sizeof(char));
    while(1){
        printf("%s\n", prompt);
        if(fgets(buf, limit, stdin) == NULL){
            fprintf(stderr, "Invalid input !!\n");
            continue;
        }
        buf[strcspn(buf, "\n")] = '\0';
        if(buf[0] == '\0'){
            print("Please enter something !");
            continue;
        }
        char* temp;
        errno = 0;
        int val = strtol(buf, &temp, 10);
        if(*buf == *temp){
            print("Please enter something !");
            continue;
        }
        if(*temp != '\0'){
            print("Please only enter numeric characters !");
            continue;
        }
        if(errno == ERANGE || val > INT_MAX || val < INT_MIN){
            print("Value out of bounds, try again.");
            continue;
        }
        free(buf);
        return val;
    }
}

float get_float(const char* prompt, size_t limit){
    char buf[limit];
    while(1){
        printf("%s\n", prompt);
        if(fgets(buf, sizeof(buf), stdin) == NULL){
            fprintf(stderr, "Invalid Input !!");
            continue;
        }
        buf[strcspn(buf, "\n")] = '\0';
        if(buf[0] == '\0'){
            print("Please enter something !");
            continue;
        }
        char* temp;
        errno = 0;
        double val = strtod(buf, &temp);
        if(*buf == *temp){
            print("Please enter something !");
            continue;
        }
        if(*temp != '\0'){
            print("Please only enter numeric characters !");
            continue;
        }
        if(errno == ERANGE){
            print("Value out of bounds, try again.");
            continue;
        }
        return (float)val;
    }
}


int main(){

    /*
    Taking in user input is tricky because users can enter invalid input and crash programs
    or sometimes user input can overwrite the data in some other variables, this is a basic rundown of how to take in user input
    the safe way
    */

    char* name = get_string("What is your name:", 100);
    printf("Hello there %s !!", name);

    int age = get_int("What is your age:", 5);
    if(age > 21){
        print("Well you can drink now, but don't drink and drive.");
    }else{
        print("Ooh, too bad buddy, but you can't drink yet.");
    }
    print("So what would you like to order:");
    print("1 = Beer ($3.12)");
    print("2 = Apple Juice ($1.32)");

    int user_choice;
    while(1){
        user_choice = get_int("Well? :", 4);
        if(user_choice == 1 || user_choice == 2){
            if(user_choice == 1 && !(age > 21)){
                print("You can't drink yet buddy .");
                continue;
            }
            break;
        }else{
            print("That's not a valid choice pal.");
        }
    }
    float amount;
    
    while(1){
        print("Well then pay up.");
        amount = get_float(">", 10);
        if(user_choice == 1 && fdim(amount, 3.12) < 0.01){
            break;
        }
        else if(user_choice == 2 && fdim(amount, 1.32) < 0.01){
            break;
        }else{
            print("That's not the right amount buddy.");
        }
    }
    print("Well then enjoy your drink pal, goodbye .");

    

    free(name);

    return 0;
}