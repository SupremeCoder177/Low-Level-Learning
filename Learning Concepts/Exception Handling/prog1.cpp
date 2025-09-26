#include <iostream>
#include <stdlib.h>

int main(){

    // this is how try catch works in c++
    // and btw there is no try/catch in c
    try{
        throw std::runtime_error("A simple demonstration purpose error"); // throwing an error on purpose
    } catch(std::exception& e){ // catching the error
        std::cout << "Caught exception : " << e.what() << std::endl; // printing the error message
    }

    return 0;
}