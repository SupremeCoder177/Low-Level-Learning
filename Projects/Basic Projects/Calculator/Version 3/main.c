#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void print(const char* string){
    unsigned int length = strlen(string);
    for(int i = 0; i < length; i++){
        putchar(string[i]);
    }
    putchar('\n');
}

int get_int(const char* prompt){
    char buf[100];
    while(1){
        printf("%s\n", prompt);
        if(fgets(buf, sizeof(buf), stdin) == NULL){
            fprintf(stderr, "Please only enter valid input.\n");
            continue;
        }

        buf[strcspn(buf, "\n")] = '\0';

        if(buf[0] == '\0'){
            fprintf(stderr, "Please enter something.\n");
            continue;
        }
        errno = 0;
        char* endptr;
        long val = strtol(buf, &endptr, 10);
        if(buf[0] == *endptr){
            printf("No valid intergers found.\n");
            continue;
        }
        if(*endptr != '\0'){
            printf("Other characters than integers entered !!\n");
            continue;
        }
        if(errno == ERANGE){
            printf("Ineger out of range. Try again.\n");
            continue;
        }

        return (int)val;
    }
}

float get_float(const char* prompt){
    char buf[100];
    while(1){
        printf("%s", prompt);
        if(fgets(buf, sizeof(buf), stdin) == NULL){
            fprintf(stderr, "Invalid input !!\n");
            continue;
        }

        buf[strcspn(buf, "\n")] = '\0';
        if(buf[0] == '\0'){
            printf("Please enter something !\n");
            continue;
        }
        errno = 0;
        char* temp;
        double val = strtod(buf, &temp);
        if(buf[0] == *temp){
            printf("Invalid input !\n");
            continue;
        }
        if(*temp != '\0'){
            printf("Other characters than numbers entered !\n");
            continue;
        }
        if(errno == ERANGE){
            printf("Entered value out of range !\n");
            continue;
        }
        return val;
    }
}

void print_commands(){
    print("0 = Exit");
    print("1 = Add");
    print("2 = Subtract");
    print("3 = Multiply");
    print("4 = Divide");
    print("5 = See current Value");
    print("6 = Reset Value");
}

int main(int argc, char* argv[]){

    print("Welcome to VERSION 3.0 Calculator CLI version");
    print("I won't bore you with the commands like usual");
    int user_input;
    double num = 0;
    float temp;
    bool exit = false;
    while(!exit){
        print("Enter 10 to see commands.");
        user_input = get_int("Enter:");
        if(user_input < 0){
            fprintf(stderr, "Commands cannot be negative values, enter 10 to see command list.");
            continue;
        }
        if(user_input == 0){
            print("Ok bye!...");
            exit = true;
            continue;
        }
        if(user_input == 5){
            printf("%f\n", num);
            continue;
        }
        if(user_input == 6){
            print("Value has been reset.");
            num = 0;
            continue;
        }
        if(user_input == 10){
            print_commands();
            continue;
        }
        if(user_input >= 1 && user_input <= 4){
            temp = get_float("Enter:");
        }
        switch(user_input){
            case 1:
                num += temp;
                break;
            case 2:
                num -= temp;
                break;
            case 3:
                num *= temp;
                break;
            case 4:
                num /= temp;
                break;
        }
    }
       
   return 0;
}