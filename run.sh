#g++ main.cpp -I utility.h
clear
g++ logger.cpp test_logger.cpp -I utility.h logger.h -pthread -std=c++11
# g++  test_ringbuffer.cpp -I utility.h  -pthread -std=c++11