#ifndef _HDEBUG
#define _HDEBUG
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "stack.h"
#include "logger.h"

const stackElem CANARY = (stackElem)0xDEADBABE;

#define DEBUG

#ifdef DEBUG
    #define DBG_PRINTF(...) printf(__VA_ARGS__)

    #define DBG_FPRINTF(fp, ...) fprintf(fp, __VA_ARGS__)

    #define DBG_FPRINTF_NO_ARGS(fp, format) fprintf(fp, format)

    #define DBG(...) __VA_ARGS__
#else
    #define DBG_PRINTF(...)

    #define DBG_FPRINTF(fp, format, ...)

    #define DBG_FPRINTF_NO_ARGS(fp, format)

    #define DBG(...)
#endif

int canary(stack *stk);
void stkNullCheck(stack *stk);
int verify(stack *stk);
void stackAssert(stack *stk);
int decoderError(FILE * fp_error, int error);

#endif
