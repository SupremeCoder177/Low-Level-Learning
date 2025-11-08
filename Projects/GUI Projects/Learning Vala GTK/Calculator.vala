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

private void print(string prompt){
    stdout.printf(@"$prompt\n");
}


public class Calculator{
    public static int main(string[] args){
        
        int num1, num2;
        while(true){
            print("Here are the commands:");
            print("1 = Add");
            print("2 = Subtract");
            print("3 = Multiply");
            print("4 = Divide");
            print("0 = Exit\n");

            int temp = get_number("Enter your choice:");
            if(temp < 0 || temp > 4){
                print("Invalid input !");
                continue;
            }
            switch(temp){
                

            }
        }

        return 0;
    }
}