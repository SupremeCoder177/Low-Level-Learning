private int get_number(string prompt){
    while(true){
        stdout.printf(prompt + "\n");
        try{
            return int.parse(stdin.read_line());
        } catch(Error e){
            stdout.printf("Input error !\n");
            stdout.printf("Try again !\n");
        }
    }
}

private float get_floating_number(string prompt){
    while(true){
        stdout.printf(prompt + "\n");
        try{
            return float.parse(stdin.read_line());
        } catch(Error e){
            stdout.printf("Input error !\n");
            stdout.printf("Try again !\n");
        }
    }
}

private float[] get_two_numbers(){
    float[] out = new float[2];
    out[0] = get_floating_number("Enter first number :");
    out[1] = get_floating_number("Enter second number :");
    return out;
}

private void print(string prompt){
    stdout.printf(@"$prompt\n");
}


public class Calculator{
    public static int main(string[] args){
        
        int num1, num2;
        bool exit = false;
        while(!exit){
            print("Here are the commands:");
            print("1 = Add");
            print("2 = Subtract");
            print("3 = Multiply");
            print("4 = Divide");
            print("0 = Exit\n");

            int choice = get_number("Enter your choice:");
            if(choice < 0 || choice > 4){
                print("Invalid input !");
                continue;
            }
            if(choice == 0) {
                exit = true;
                continue;
            }
            float[] temp = new float[2];
            temp = get_two_numbers();
            float result = 0;
            switch(choice){
                case 1:
                    result = temp[0] + temp[1];
                    break;
                case 2:
                    result = temp[0] - temp[1];
                    break;
                case 3:
                    result = temp[0] * temp[1];
                    break;
                case 4:
                    result = temp[0] / temp[1];
                    break;
            }
            stdout.printf(@"Here is the result : $result\n");
        }

        return 0;
    }
}