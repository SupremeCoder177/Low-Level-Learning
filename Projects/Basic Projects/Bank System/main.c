#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_NAME_SIZE 100

typedef char* USER_NAME;
typedef int AMOUNT;

char* DATA[] = {"John Doe  password123"};

void print(const char* str){
    size_t length = strlen(str);
    for(size_t i = 0; i < length; ++i){
        putchar(str[i]);
    }
    putchar('\n');
}

int get_int(){
    char buf[100];
    while(true){
        if(fgets(buf, sizeof(buf), stdin) == NULL){
            fprintf(stderr, "Invalid Input !");
            continue;
        }
        buf[strcspn(buf, "\n")] = '\0';
        if(buf[0] == '\0'){
            fprintf(stderr, "Please enter a choice.");
            continue;
        }

        char* temp;
        int val = strtol(buf, &temp, 10);
        if(buf[0] ==  *temp){
            print("Please enter a choice.");
            continue;
        }
        if(*temp != '\0'){
            fprintf(stderr, "Please only enter numeric characters.");
            continue;
        }
        if(errno == ERANGE){
            fprintf(stderr, "Entered number out of range !");
            continue;
        }
        return val;
    }
}

void get_string(char* str){
    while(true){
        if(fgets(str, sizeof(str), stdin) == NULL){
            fprintf(stderr, "EOF or user input error has occured, please try again.");
            continue;
        }else{
            break;
        }
    }
}


bool check_name(char* name){
    size_t len = strlen(name);
    char get[len];
    char* temp;
    strncpy(temp, name, len);
    if(strncmp(name, temp)){
        print("");
    };
}

void print_pre_commands(){
    print("1 = Login");
    print("2 = Open new account");
}

void print_after_commands(){
    print("1 = See Balance");
    print("2 = Withdraw");
    print("3 = Deposit");
}

int main(){
    bool exit = false;
    int user_input;
    char curr_name[MAX_NAME_SIZE];
    char password[MAX_NAME_SIZE];
    print("Welcome to the Bank of Universe");
    print("How can we be of service today?");
    while(!exit){
        print("Enter 0 to exit and 10 to see command options.");
        user_input = get_int();
        if(user_input == 0){exit = true;}
        if(user_input == 10){print_pre_commands();}
        if(user_input == 1){
            print("Enter you name please:");
            get_string(curr_name);
            check_name(curr_name);
            print("Enter you password:");
            get_string(password);
        }
        if(user_input == 2){

        }
    }
    
}