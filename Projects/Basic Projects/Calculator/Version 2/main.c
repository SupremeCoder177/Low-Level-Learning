#include <stdio.h>
#include <string.h>

// basically copying the print function from the python language with some dependency that we need to pass the lenght of the string as well
void print(const char* string){
    int length = strlen(string);
    for(unsigned int i = 0; i < length; i++){
        putchar(string[i]);
    }
    putchar('\n');
}

// asks the user to enter a floating point number 
// if they don't comply, well then it puts them in a loop
float ask_float(){
    float output = -1;
    while(1){
        print("Enter a number :");
        if(scanf("%f", &output) == 1){break;}
        else{print("Invalid input ma boi .");}
    }
    return output;
}

int main(){

    print("Welcome to another CLI calculator app !");

    const char* insults[] = {
        "Invalid input !!",
        "Don't do that, be a good boy and only enter the commands",
        "Really bro, just stick to the commands"
    };
    unsigned short curr_insult = 0;
    unsigned short total_insults = sizeof(insults) / sizeof(insults[0]);
    
    int user_input = -1;
    float num = 0;
    float temp;
    do{
        print("Commands : 0 = Exit\n1 = Add\n2 = Subtract\n3 = Multiply\n4 = Divide\n5 = See Result");
        print("After seeing result, the number is set back to 0.");
        if(scanf("%d", &user_input) == 1){
            if(user_input == 0){break;}
            if(user_input != 5 && user_input > 0 && user_input <= 4){temp = ask_float();}
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
                    if(temp != 0){
                        num /= temp;
                    }else{
                        print("You do know that you cannot divide by zero right ?");
                    }
                    break;
                case 5:
                    printf("%f\n", num);
                    num = 0;
                    break;
                default:
                    print(insults[curr_insult]);
                    curr_insult = (curr_insult + 1) % total_insults;
            }
        }else{
            print(insults[curr_insult]);
            curr_insult = (curr_insult + 1) % total_insults;
        }
    }while(user_input != 0);

    return 0;
}