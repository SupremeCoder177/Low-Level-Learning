// A simple hello world program with basic syntax

class Demo.HelloWorld : GLib.Object{
    public static int main(string[] args){
        stdout.printf("Hello world\n");

        // declaring variables
        int a = 12;
        int b = 23;

        // a unichar stores a 32 bit unicode character
        unichar myChar = 'u';

        // whereas a char stores a simple 8 bit character defined in the ASCII encoding
        char newChar = 'a';

        long num1 = 12356362;
        ulong num2 = 56867536;

        // this is how you use string templates
        stdout.printf(@"$a + $b = $(a + b)\n");

        // printing more stuff
        stdout.printf(@"num1 = $num1\n");
        stdout.printf(@"num2 = $num2\n");

        // a simple string
        string aString = "This is a string, it can be as long as you want, but it is immutable.\n";

        // a verbatim string
        string verbatim = """This is an exmaple of a string which preservers the line-breaks
you can use this to write long paragraphs and while printing it 
will appear as formmatted in the code.
""";

        stdout.printf(aString);
        stdout.printf(verbatim);

        // parsing strings to other data types

        bool c = bool.parse("false");
        int d = int.parse("-43");
        double e = double.parse("6.2343434E-11");

        stdout.printf(@"c, d, e = $c $d $e\n");

        // parsing data types to string
        string s1 = true.to_string();
        string s2 = 21.to_string();

        stdout.printf(@"$s1\n");
        stdout.printf(@"$s2\n");
        
        return 0;
    }
}