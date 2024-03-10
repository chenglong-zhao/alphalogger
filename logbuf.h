#ifndef LOGGER_HEADER_
#define LOGGER_HEADER_

#include <string.h>
#include "utility.h"

#define BUFSIZE   1024 // 1KB
#define QUEUESIZE 256 // 

class LogBuffer {
  public:
    LogBuffer();
    LogBuffer(const char *line, int len);
    LogBuffer(const LogBuffer& logbuf);
    LogBuffer& operator=(const LogBuffer& logbuf); 
    ~LogBuffer();
    void Write(const char* line,  int len);
    // void Flush();

  public:
    int len_;
    char *logger_buffer_;
    unsigned int buffer_size_;
};


#endif 