#include <iostream>
#include <string>

#include "utility.h"

int main(){

    RingBuffer<std::string> test_tf(5);
    test_tf.Push("1");
    test_tf.Push("2");
    test_tf.Push("3");
    std::cout << test_tf.Pop() << std::endl;

}