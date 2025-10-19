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


public class Calculator{
    public static int main(string[] args){
        
        
        return 0;
    }
}