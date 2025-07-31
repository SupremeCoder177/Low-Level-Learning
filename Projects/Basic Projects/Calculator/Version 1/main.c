#include <stdio.h>

int main(int argc, char* argv[]){
    //Greeting the user
    printf("Welcome to my calculator CLI app !\n");
    
    int user_choice = -1;
    float num1, num2;
    do{
        printf("Here are the commands you can access\n");
        printf("0 = Exit\n");
        printf("1 = Add\n");
        printf("2 = Subtract\n");
        printf("3 = Multiply\n");
        printf("4 = Exit\n");
        printf("Anything else = Nothing will happen bruh.\n");
        scanf("%d", &user_choice);
        if(user_choice == 0){break;}
        printf("Great now enter two numbers:");
        if (scanf("%f %f", &num1, &num2) == 2){
            switch (user_choice){
            case 1:
                printf("%f\n", num1 + num2);
                break;
            case 2:
                printf("%f\n", num1 - num2);
                break;
            case 3:
                printf("%f\n", num1 * num2);
                break;
            case 4:
                printf("%f\n", num1 / num2);
                break;
            default:
                printf("Told you man nothing will happen.");
            }
        }
    }while(user_choice != 0);
    return 0;
}