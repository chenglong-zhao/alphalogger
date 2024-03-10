#include "logbuf.h"

//logbuffer

LogBuffer::LogBuffer():
    buffer_size_(BUFSIZE) {
    logger_buffer_ = new char[buffer_size_];
};

LogBuffer::LogBuffer(const char *line, int len):
    buffer_size_(BUFSIZE), 
    len_(len){
    logger_buffer_ = new char[buffer_size_];
    memcpy(logger_buffer_, line, len);
};

LogBuffer::LogBuffer(const LogBuffer& logbuf) {   
    buffer_size_ = BUFSIZE;
    len_ =  logbuf.len_;
    logger_buffer_ = new char[buffer_size_];
    memcpy(logger_buffer_, logbuf.logger_buffer_, logbuf.len_);
};

LogBuffer& LogBuffer::operator=(const LogBuffer& logbuf){
    buffer_size_ = BUFSIZE;
    len_ =  logbuf.len_;
    logger_buffer_ = new char[buffer_size_];
    memcpy(logger_buffer_, logbuf.logger_buffer_, logbuf.len_);
    return *this;
};

LogBuffer::~LogBuffer( ){
    delete [] logger_buffer_;
};

void LogBuffer::Write(const char* line,  int len)
{   
    len_ = len;
    memcpy(logger_buffer_, line, len);
};