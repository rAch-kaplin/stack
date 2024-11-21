#include "logger.h"
#include "color.h"



int loggerInit(const char *log_file_name, const char *error_log_file_name)
{
    Logger* log = GetLogger();
    log->logFile = fopen(log_file_name, "w+");
    if (log->logFile == NULL)
    {
        fprintf(stderr, "logFile failed open\n");
        return -100;
    }

    log->errorLogFile = fopen(error_log_file_name, "w+");
    if (log->errorLogFile == NULL)
    {
        fprintf(stderr, "logFile failed open\n");
        return -100;
    }
    return 0;
}


void loggerDeinit()
{
    Logger* log = GetLogger();
    fclose(log->logFile);
    log->logFile = NULL;

    fclose(log->errorLogFile);
    log->errorLogFile = NULL;
}


Logger* GetLogger()
{
    static Logger logger = {NULL, NULL};
    return &logger;
}

void logStack(const stack *stk, LogLevel level)
{
    Logger* log = GetLogger();
    FILE *logFile = NULL;

    if (!log)
    {
        fprintf(stderr, "Logger is NULL\n");
        return;
    }

    switch(level)
    {
        case LOG_INFO:
            logFile = log->logFile;
            break;
        case LOG_ERROR:
            logFile = log->errorLogFile;
            break;
        default:
            return;
    }

    if (!logFile)
    {
        fprintf(stderr, "logFile is NULL\n");
        return;
    }

    dump(stk, logFile);
}

errorCode dump(const stack *stk, FILE *logFile)
{
    if (stk == NULL)
    {
        fprintf(stderr, "stk is NULL\n");
        return STK_STRUCT_NULL_POINTER;
    }

    fprintf(logFile, "=========================================================================================\n");
    fprintf(logFile, "STACK DUMP [INFO]:\n");
    fprintf(logFile, "stack pointer = %p\n", stk);
    fprintf(logFile, "Capacity: %zu\n", stk->capacity);
    fprintf(logFile, "Size: %zd\n", stk->size);
    fprintf(logFile, "Data pointer: %p\n", stk->data);
    fprintf(logFile, "Data: ");
    for (size_t i = 0; i < stk->capacity; i++) {
        fprintf(logFile, STACK_ELEM_FORMAT " ", stk->data[i]);
    }
    fprintf(logFile, "\n");

    return STK_OK;
}
