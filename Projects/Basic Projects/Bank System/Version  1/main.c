#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>

#define MAX_NAME_LEN 100
#define MIN_NAME_LEN 12
#define MAX_PASSWORD_LEN 20
#define MIN_PASSWORD_LEN 10
#define DATA_LENGTH 20
#define READ_LENGTH MAX_NAME_LEN + MAX_PASSWORD_LEN + DATA_LENGTH + 2 * 3 + 1
#define WRITE_LEN READ_LENGTH
#define MIN_START_AMOUNT 3 // 3 digit sum
#define MAX_AMOUNT 12 // 12 digit number
#define UNUSED_SLOT 96 // translates to ` in ASCII

char user_name[MAX_NAME_LEN + 1]; //to account for the \0 at the end
char password[MAX_PASSWORD_LEN + 1];
char* FILE_NAME = "data.txt";

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

void get_amount(char* prompt, char* buf, size_t len){
    while(1){
        printf("%s\n", prompt);
        if(fgets(buf, len, stdin) == NULL){
            fprintf(stderr, "An error has occured, please try again .");
            continue;
        }

        buf[strcspn(buf, "\n")] = '\0';
        if(buf[0] == '\0'){
            fprintf(stderr, "Please enter a choice.");
            continue;
        }
        char* temp;
        errno = 0;
        float val = strtof(buf, &temp);
        if(buf[0] == *temp){
            print("Please enter something !");
            continue;
        }
        if(*temp != '\0'){
            print("Please only enter numeric values.");
            continue;
        }
        if(errno == ERANGE){
            print("Entered value out of range ! Try again.");
            continue;
        }
        if(val < 0){
            print("Please only enter positive numbers.");
            continue;
        }
        int min_val = pow(10, MIN_START_AMOUNT);
        if(!(val - min_val >= 0)){
            print("Minimum starting amount is 1000.");
            continue;
        }
        break;
    }
}

void get_string(char* str, size_t len){
    while(true){
        if(fgets(str, len, stdin) == NULL){
            fprintf(stderr, "User input error has occured, please try again.");
            continue;
        }
        str[strcspn(str, "\n")] = '\0';
        if(str[0] == '\0'){
            print("Please enter something .");
            continue;
        }else{break;}
    }
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

bool check_info(){
    FILE* f = fopen(FILE_NAME, "r");
    char buf[READ_LENGTH];
    char name[MAX_NAME_LEN];
    char pass[MAX_PASSWORD_LEN];
    size_t offset = 0;
    while(fgets(buf, sizeof(buf), f) != NULL){
        for(size_t i = 0; i < MAX_NAME_LEN; ++i){
            if(buf[i] == UNUSED_SLOT){continue;}
            else{name[i] = buf[i];}
            offset++;
        }
        for(size_t i = 0; i < MAX_PASSWORD_LEN; ++i){
            if(buf[i + offset] == UNUSED_SLOT){continue;}
            else{pass[i] = buf[i + offset];}
            offset++;
        }
        printf("%s\n", name);
        printf("%s\n", pass);
    }
    fclose(f);
}

void convert_to_string(const char* buf, float val){

}

void make_info(const char* amount){
    FILE* f = fopen(FILE_NAME, "a");
    char buf[WRITE_LEN];
    printf("%s\n", user_name);
    printf("%s\n", password);
    printf("%s\n", amount);
    size_t offset = 0;
    for(size_t i = 0; i < MAX_NAME_LEN; ++i){
        if(i < strlen(user_name)){
            buf[i] = user_name[i];
        }else{
            buf[i] = UNUSED_SLOT;
        }
        offset++;
    }
    for(size_t i = 0; i < MAX_PASSWORD_LEN; ++i){
        if(i < strlen(password)){
            buf[i + offset] = password[i];
        }else{
            buf[i + offset] = UNUSED_SLOT;
        }
        offset++;
    }
    for(size_t i = 0; i < MAX_AMOUNT; ++i){
        if(i < strlen(amount)){
            buf[i + offset] = amount[i];
        }else{
            buf[i + offset] = UNUSED_SLOT;
        }
        offset++;
    }
    fputs(buf, f);
    fclose(f);
}

void enter_login_mode(){

}

int main(){
    bool exit = false;
    int user_input;
    print("Welcome to the Bank of Universe");
    print("How can we be of service today?");
    while(!exit){
        print("Enter 0 to exit and 10 to see command options.");
        user_input = get_int();
        if(user_input == 0){
            print("Aw, leaving already? Well alright bye then !");
            exit = true;}
        if(user_input == 10){print_pre_commands();}
        if(user_input == 1){
            print("Enter your name please:");
            get_string(user_name, MAX_NAME_LEN);
            print("Enter your password:");
            get_string(password, MAX_PASSWORD_LEN);
            if(strlen(user_name) < MIN_NAME_LEN){printf("Username cannot be less than %d characters.\n", MIN_NAME_LEN);continue;}
            if(strlen(password) < MIN_PASSWORD_LEN){printf("Password cannot be less than %d characters.\n");continue;}
            if(check_info()){
                enter_login_mode();
            };
        }
        if(user_input == 2){
            print("Enter your username please:");
            get_string(user_name, MAX_NAME_LEN);
            print("Enter your password:");
            get_string(password, MAX_PASSWORD_LEN);
            if(strlen(user_name) < MIN_NAME_LEN){printf("Username cannot be less than %d characters.\n", MIN_NAME_LEN);continue;}
            if(strlen(password) < MIN_PASSWORD_LEN){printf("Password cannot be less than %d characters.\n");continue;}
            char amount[MAX_AMOUNT];
            get_amount("Enter amount:", amount, sizeof(amount));
            make_info(amount);
        }
    }
    
}