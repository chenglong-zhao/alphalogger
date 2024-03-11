#include <iostream>

void print_char(const char* line){
    std::cout<< *line <<std::endl;
}

int main(){
    int a = 32;
    print_char("hello world");
    const char * s = "how are you";
    std::cout<< s <<std::endl;

}