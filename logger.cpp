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

    fprintf(logFile, "=========================================================================================\n");
    fprintf(logFile, "STACK DUMP:\n");
    fprintf(logFile, "Capacity: %zu\n", stk->capacity);
    fprintf(logFile, "Size: %zu\n", stk->size);
    fprintf(logFile, "Data: ");
    for (size_t i = 0; i < stk->capacity; i++) {
        fprintf(logFile, "%d ", stk->data[i]);
    }
    fprintf(logFile, "\n");
}
