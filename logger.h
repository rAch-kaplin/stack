#ifndef _HLOGGER
#define _HLOGGER

#include <stdio.h>
#include "stack.h"

#define LOG(levelMsg, fmt, ...)                                  \
    do                                                           \
    {                                                            \
        if (shouldLog(levelMsg))                                 \
        {                                                        \
            log(levelMsg, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
        }                                                        \
    } while(0)

enum LogLevel
{
    LOGL_DEBUG = 0,
    LOGL_INFO  = 1,
    LOGL_ERROR = 2
};


typedef struct {
    LogLevel levelLogger;
    FILE *logFile;
} Logger;


bool shouldLog(LogLevel levelMsg);
int loggerInit(LogLevel levelLogger, const char *log_file_name);
void loggerDeinit();
Logger* GetLogger();
//void log(LogLevel levelMsg, const char* fmt, ...);
void log(LogLevel levelMsg, const char* file, int line, const char* fmt, ...);
void dump(const stack *stk);


#endif
