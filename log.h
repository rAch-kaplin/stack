#pragma once

bool ShouldLog(LogLevel levelMsg);

// vargs
void Log(LogLevel levelMsg, const char* fmt, ...);

#define LOG(levelMsg, fmt, ...)              \
    do                                       \
    {                                        \
        if (ShouldLog(levelMsg))             \
        {                                    \
            Log(levelMgs, fmt, __VA_ARGS__); \
        }                                    \
    } while (0)

LOG(LOGL_DEBUG, "%ld", factorial(1000000));
LOG(LOGL_DEBUG, "%ld", factorial(100));


// examples
struct Logger
{
    LogLevel levelLogger;
}

LOG(LOGL_DEBUG, "%ld", factorial(1000000));

Logger* GetLogger()
{
    static Logger logger = {};
    return &logger;
}

enum LogLevel
{
    LOGL_DEBUG = 0,
    LOGL_INFO  = 1,
    LOGL_ERROR = 2,
};

void LogInit(LogLevel levelLogger)
{
    GetLogger()->levelLogger = levelLogger;
}

bool ShouldLog(LogLevel levelMsg)
{
    return GetLogger()->levelLogger <= levelMsg;
}
