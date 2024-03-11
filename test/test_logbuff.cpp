#include <iostream>
#include <string>
#include "utility.h"
#include "logbuf.h"

int main(){

    RingBuffer<std::string> test_buf(5);
    char s[1024] = "hello world";
    test_buf.Push(s);
    test_buf.Push("tmp12");
    test_buf.Push("tmp3");

    // RingBuffer<LogBuffer> test_buf(5);
    // for(int i=1; i< 10; i++){
    //     char const *tmp = "123";
    //     LogBuffer logbuf(tmp, 5);
    //     test_buf.Push(logbuf);
    // }
    std::string tmp_buff = test_buf.Pop();
    std::cout << tmp_buff << std::endl;
    // std::cout << tmp_buff.len_ << std::endl;
    // std::cout << tmp2.len_ << std::endl;

    return 0;
}