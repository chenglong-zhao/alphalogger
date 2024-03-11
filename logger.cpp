#include "logger.h"

const char * LevelString[5] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};

Logger::Logger():
    log_level_(LogLevel::INFO),
    log_fp_(nullptr){
        ;
}

Logger::~Logger(){
    if(log_fp_ != nullptr) {
    fclose(log_fp_);
    }
    if(flushthread_.joinable())
        flushthread_.join();
}

void Logger::Init(const char* logdir, LogLevel level){ 
    time_t t = time(nullptr);
    struct tm *ptm = localtime(&t);
    
    char logfile[256] = {0};
    snprintf(logfile, 255, "%s/log_%d_%d_%d", logdir,
                ptm->tm_year+1900,
                ptm->tm_mon+1,
                ptm->tm_mday);

    log_fp_  = fopen(logfile, "w+");
    if (log_fp_ == nullptr)
        std::cout << "open fp failed !" << std::endl;

    log_level_ = level;
    flushthread_ = std::thread(&Logger::Flush, this);

}

void Logger::Write(int level, const char *file, int line, const char *func, const char *fmt, ...){
    char logline[LOGLINESIZE];
    
    // std::cout << file << std::endl;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    static time_t lastsec = 0;
    if(lastsec != tv.tv_sec) {
        struct tm *ptm = localtime(&tv.tv_sec);  
        lastsec = tv.tv_sec;      
        int k = snprintf(save_ymdhms_, 64, "%04d-%02d-%02d %02d:%02d:%02d", ptm->tm_year+1900, \
            ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        save_ymdhms_[k] = '\0';
    }

    uint32_t n = snprintf(logline, LOGLINESIZE, "[%s][%s.%03ld][%s:%d %s]", LevelString[level], \
        save_ymdhms_, tv.tv_usec/1000, file, line, func);

    va_list args;
    va_start(args, fmt);
    int m = vsnprintf(logline + n, LOGLINESIZE - n, fmt, args);
    va_end(args);
    int len = n + m;

    logger_buffer_.Push(logline);

}

void Logger::Flush(){
    while (true)
    {
        // std::cout << logger_buffer_.isEmpty() << std::endl;
        if(logger_buffer_.isEmpty())
            ;
        else{
            std::string tmp = logger_buffer_.Pop();
            // std::cout << "Flush" << tmp << std::endl;
            size_t n = fwrite(tmp.c_str(), sizeof(char), tmp.size(), log_fp_);
        
        }
    }
}


