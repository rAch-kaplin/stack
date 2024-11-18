#ifndef _HDEBUG
#define _HDEBUG
#include <stdio.h>
#include "stack.h"
#include "logger.h"


#define DEBUG

#ifdef DEBUG
    #define DBG_PRINTF(...) printf(__VA_ARGS__)

    #define DBG_FPRINTF(fp, format, ...) fprintf(fp, format, __VA_ARGS__)

    #define DBG_FPRINTF_NO_ARGS(fp, format) fprintf(fp, format)

    #define DBG(...) __VA_ARGS__
#else
    #define DBG_PRINTF(...)

    #define DBG_FPRINTF(fp, format, ...)

    #define DBG_FPRINTF_NO_ARGS(fp, format)

    #define DBG(...)
#endif

errorCode verify(const stack *stk);
void stackAssert(stack *stk);

#endif
