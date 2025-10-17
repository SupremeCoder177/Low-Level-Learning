public class TakingInputs{
    public static int main(string[] args){

        stdout.printf("Let's take in some CLI inputs shall we.\n");

        stdout.printf("What is your name?\n");
        // the stdin.read_line functions reads a single line from console
        string username = stdin.read_line().strip();
        int name_length = username.length;
        stdout.printf(@"Hello there $username\n");

        stdout.printf("How old are you?\n");
        int age = int.parse(stdin.read_line());

        if(age >= 18){
            stdout.printf("Oh so you are an adult.\n");
        }else{
            stdout.printf("You are not an adult yet buddy.\n");
            return 0;
        }

        stdout.printf(@"Ok so buddy $username, you can continue.\n");
        stdout.printf("Welcome to the club.\n");

        return 0;
    }
}