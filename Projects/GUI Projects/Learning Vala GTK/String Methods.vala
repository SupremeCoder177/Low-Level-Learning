public class Demo.StringMethods{
    public static int main(string[] args){
        
        // there are a lot of in built string methods
        // but here are the most commonly used ones

        string a = "this is a string";
        int len = a.length;

        stdout.printf(@"a = $a\n");
        stdout.printf(@"Length of a : $len\n");

        // splitting the string into an array with the delimeter being a " "
        string[] words = a.split(" ");

        // displaying the contents of the array
        foreach (string word in words) stdout.printf(@"$word\n");

        // substrings
        string b = "Hello World";
        string sub1 = b.substring(2, 4);
        string sub2 = b.substring(-3, -1);

        stdout.printf(@"sub1 = $sub1\n");
        stdout.printf(@"sub2 = $sub2\n");

        // checking for needles in a string
        string c = "This is a really long paragraph designed to act as an example for finding a substring in a string.";
        stdout.printf(@"Haystack : $c\n");
        
        string word = "para";
        bool contains_words = c.contains(word);

        stdout.printf(@"Haystack contains ($word) ? : $contains_words\n");

        // converting a string to upper case or lowercase
        string upper = b.up();
        string lower = b.down();

        stdout.printf(@"Uppercase of ($b) : $upper\n");
        stdout.printf(@"Lowercase of ($b) : $lower\n");

        // removing trailing spaces
        string d = "Something          ";
        d = d.chomp();
        stdout.printf(@"d = $d\n");

        // removing all leading and trailing white spaces
        string e = "     Another Thing     ";
        e = e.strip();
        stdout.printf(@"e = $e\n");

        return 0;

    }
}