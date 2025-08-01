#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print(const char* string){
    unsigned int length = strlen(string);
    for(int i = 0; i < length; i++){
        putchar(string[i]);
    }
    putchar('\n');
}

bool checkInInt(int* nums, int length, int num){
    for(int i = 0; i < length; i++){
        if(nums[i] == num){
            return true;
        }
    }
    return false; 
}

int main(int argc, char* argv[]){
    
    double num = 0;
    char* name[100];
    int valid_inputs[] = {1, 2, 3, 4, 0};
    int user_input = -1;
    print("Welcome again to my calculator CLI app.");
    print("Care to tell me your name, this is our third time meeting after all:");
    scanf("%100s", name);
    printf("Hello there %s\n", name);

    do{
        printf("Current Number : %f\n", num);
        print("Well here are the commands:");
        print("0 = Exit");
        print("1 = Add");
        print("2 = Sub");
        print("3 = Multiply");
        print("4 = Divide");
        scanf("%d", user_input);
        if(!checkInInt(valid_inputs, sizeof(valid_inputs) / sizeof(valid_inputs[0]), user_input)){
            print("Come on bro just enter the valid commands.");
            break;
        }else{
            switch (user_input)
            {
            case 0:
                break;
            default:
                break;
            }
        }
    }while(user_input != 0);
    return 0;
}