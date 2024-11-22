#include "logger.h"
#include "color.h"
#include "debug.h"
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>

// vargs
//void log(LogLevel levelMsg, const char* fmt, ...);
//bool shouldLog(LogLevel levelMsg);

Logger* GetLogger()
{
    static Logger logger = {LOGL_DEBUG, NULL};
    return &logger;
}

int loggerInit(LogLevel levelLogger, const char *log_file_name)
{
    Logger* log = GetLogger();
    log->levelLogger = levelLogger;
    log->logFile = fopen(log_file_name, "w+");

    if (log->logFile == NULL)
    {
        fprintf(stderr, "logFile failed open\n");
        return -100;
    }

    return 0;
}

bool shouldLog(LogLevel levelMsg)
{
    return GetLogger()->levelLogger <= levelMsg;
}

void log(LogLevel levelMsg, const char* file, int line, const char* fmt ...)
{
    time_t time_now = time(NULL);
    struct tm *now = localtime(&time_now);
    char time_info[30] = {};
    strftime(time_info, sizeof(time_info), "%Y-%m-%d %H:%M:%S", now);

    const char *levelStr;

    switch(levelMsg)
    {
        case LOGL_DEBUG:
            levelStr = "DEBUG";
            break;
        case LOGL_INFO:
            levelStr = "INFO";
            break;
        case LOGL_ERROR:
            levelStr = "ERROR";
            break;
        default:
            break;
    }

    FILE *logFile = GetLogger()->logFile;
    if (!logFile)
    {
        fprintf(stderr, "logFile is NULL\n");
        return;
    }
    va_list args;
    va_start(args, fmt);
    fprintf(logFile, "[%s][%s][%s][%s:%d]:", time_info, levelStr, file , file, line);
    vfprintf(logFile, fmt, args);
    //dump(stk);
    va_end(args);

    //fprintf(logFile, "\n");
    fflush(logFile);
}


void loggerDeinit()
{
    Logger* log = GetLogger();
    fclose(log->logFile);
    log->logFile = NULL;

}

void dump(const stack *stk)
{
    stkNullCheck(stk);

    FILE *logFile = GetLogger()->logFile;


    fprintf(logFile, "=========================================================================================\n"
                     "\tSTACK DUMP:\n"
                     "\tstack pointer = %p\n"
                     "\tCapacity: %zd\n"
                     "\tSize: %zd\n"
                     "\tData pointer: %p\n"
                     "\tData: ", stk, stk->capacity, stk->size, stk->data);
    for (ssize_t i = 0; i < stk->capacity + 2; i++)
    {
        fprintf(logFile, " " STACK_ELEM_FORMAT , stk->data[i]);
    }
    fprintf(logFile, "\n");

}
