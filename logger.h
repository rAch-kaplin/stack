#ifndef _HLOGGER
#define _HLOGGER

#include <stdio.h>
#include "stack.h"

#define LOG(levelMsg, fmt, stk, ...)                                           \
    do                                                                         \
    {                                                                          \
        if (shouldLog(levelMsg))                                               \
        {                                                                      \
            log(levelMsg, __FILE__, __LINE__, __func__, fmt, stk, __VA_ARGS__);\
        }                                                                      \
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
const char* СolorLogMsg(const enum LogLevel levelMsg);
//void log(LogLevel levelMsg, const char* fmt, ...);
void log(LogLevel levelMsg, const char *file, size_t line, const char *func,  const char *fmt, stack *stk, ...);
void dump(const stack *stk);


#endif
