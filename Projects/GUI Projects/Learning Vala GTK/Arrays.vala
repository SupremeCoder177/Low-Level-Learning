public class ArrayDemo{
    public static int main(string[] args){

        // Let's talk about arrays in vala
        // Here is the basic syntax to make an array
        // data_type[] identifier = new data_type[size];
        // or
        // data_type[] identifier = {values.....};

        int[] a = new int[10];
        a[0] = 10;
        a[1] = 12;

        int[] b = {1, 2, 3, 4};

        stdout.printf("Array (a) : ");
        foreach(int i in a) stdout.printf(@"$i ");
        stdout.printf("\n");

        stdout.printf("Array (b) : ");
        foreach(int i in b) stdout.printf(@"$i ");
        stdout.printf("\n");

        // array slicing, End index is exclusive
        int[] c = b[1:3];

        stdout.printf("Array (c) : ");
        foreach(int i in c) stdout.printf(@"$i ");
        stdout.printf("\n");


        // Creating Multidimensional arrays
        int[,] d = {{2, 3, 4, 5},
                    {3, 5, 7, 8},
                    {5, 8, 6, 0}
                   };
        
        // refrencing a multidimensional array item
        d[2, 3] = 42;

        stdout.printf("Array (d) : ");
        foreach(int i in d){
            stdout.printf(@"$i ");
        }
        stdout.printf("\n");

        return 0;
    }
}