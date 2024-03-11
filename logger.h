#ifndef LOGGER_HEADER_
#define LOGGER_HEADER_

#include <string>
#include <ctime>
#include <cstdio>
#include <sys/time.h>
#include <iostream>
#include <cstdint>
#include <thread>
#include <stdarg.h>

#include "utility.h"

#define BUFSIZE 1024
#define LOGLINESIZE 1024


class Logger;

#define LOG_INIT(logdir, lev) \
    do { \
        Logger::GetInstance()->Init(logdir, lev); \
    } while (0)

#define LOG(level, fmt, ...) \
    do {  \
        if(Logger::GetInstance()->GetLevel() <= level) {  \
            Logger::GetInstance()->Write(level, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__);  \
        }  \
    } while (0)  


enum LogLevel {
  DEBUG=0,
  INFO,
  ERROR,
  FATAL,
};


class Logger {
  public:
    void Write(int level, const char *file, int line, const char *func, const char *fmt, ...);
    void Init(const char* logdir, LogLevel level);
    void Flush();
    int GetLevel() const {
        return log_level_;
    }

    static Logger * GetInstance() {
        static Logger logger;
        return &logger;
    }

  public:

  private:
    Logger();
    ~Logger();

  private:
    FILE *log_fp_;
    char save_ymdhms_[64];
    int log_level_;
    std::thread flushthread_;
    RingBuffer<std::string, BUFSIZE> logger_buffer_;


};


#endif 