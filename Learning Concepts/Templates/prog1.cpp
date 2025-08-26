#include <iostream>
#include <string>

//templates basically allow to write usable code for various types
// the T is a type holder for whichever type the object was instantiated with

template <typename T>
T maximum(T a, T b){
    return (a > b) ? a : b;
}

template <typename T>
class Biotic{

    public:
    T stuff;
    Biotic(){
        std::cout << "Inside the constructor" << std::endl;
    }

};

int main(){
    
    Biotic<int> bio = Biotic<int>();
    std::cout << maximum(20, 10) << std::endl;
    std::cout << maximum('A', 'v') << std::endl;
    std::cout << maximum(std::string("dsg"), std::string("sgdh")) << std::endl;

    return 0;
}