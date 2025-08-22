#include <iostream>
#include <string>
#include <cstdint>

class Human{
    public:
        std::string name;
        int age;

        Human(std::string name, int age){
            this->name = name;
            this->age = age;
        }

        void talk(){
            std::cout << "Hello my name is " << this->name << " and I am "<< this->age << " years old !" << std::endl;
        }
};


int main(int argc, char* argv[]){
    Human h1 = Human("Mary Jane", 23);
    h1.talk();
    return 0;
}