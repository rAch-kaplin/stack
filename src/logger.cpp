#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include "logger.h"
#include "color.h"
#include "debug.h"

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
    GetLogger()->levelLogger = levelLogger;
    GetLogger()->logFile = fopen(log_file_name, "w+");

    if (GetLogger()->logFile == NULL)
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


const char* ColorLogMsg(const enum LogLevel levelMsg)
{
    switch (levelMsg)
    {
        case LOGL_DEBUG:
            return "[DEBUG]";
            break;

        case LOGL_INFO:
            return "[INFO]";
            break;

        case LOGL_ERROR:
            return "[ERROR]";
            break;

        default:
            break;
    }

    return "UNKNOW";
}


void log(LogLevel levelMsg, const char *file, size_t line, const char *func,  const char *fmt, stack *stk, ...)
{
    time_t time_now = time(NULL);
    struct tm *now = localtime(&time_now);
    char time_info[30] = {};
    strftime(time_info, sizeof(time_info), "%Y-%m-%d %H:%M:%S", now);

    if (!GetLogger()->logFile)
    {
        fprintf(stderr, "logFile is NULL\n");
        return;
    }
    va_list args;
    va_start(args, fmt);
    fprintf(GetLogger()->logFile, "[%s]%s[%s][%zu:%s]:", time_info, ColorLogMsg(levelMsg), file , line, func);
    vfprintf(GetLogger()->logFile, fmt, args);
    dump(stk);
    va_end(args);

    //fprintf(logFile, "\n");
    fflush(GetLogger()->logFile);
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

    fprintf(GetLogger()->logFile,
                     "\tstack pointer = %p\n"
                     "\tCapacity: %zu\n"
                     "\tSize: %zd\n"
                     "\tData pointer: %p\n"
                     "\tData: ", stk, stk->capacity, stk->size, stk->data);
    for (size_t i = 0; i < stk->capacity + 2; i++)
    {
        fprintf(GetLogger()->logFile, " " STACK_ELEM_FORMAT , stk->data[i]);
    }

    fprintf(GetLogger()->logFile, "\n");

}
