#ifndef _HLOGGER
#define _HLOGGER

#include <stdio.h>
#include "stack.h"

typedef struct {
    FILE *logFile;
    FILE *errorLogFile;
} Logger;

enum LogLevel
{
    LOG_INFO,
    LOG_ERROR
};

int loggerInit(const char *log_file_name, const char *error_log_file_name);
void loggerDeinit();
Logger* GetLogger();
void logStack(const stack *stk, LogLevel level);
errorCode dump(const stack *stk, FILE *logFile);


#endif
