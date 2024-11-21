#include "debug.h"


errorCode verify(const stack *stk)
{
    if (stk == NULL)
        return STK_STRUCT_NULL_POINTER;

    if (stk->data == NULL)
        return STK_OUT_MEMORY;

    if ((size_t)stk->size > stk->capacity)
        return STK_SIZE_LARGER_CAPACITY;

    if (stk->size < 0)
        return BAD_SIZE;

    if (stk->capacity == 0)
        return STK_CAPACITY_NOT_EXSIST;


    return STK_OK;
}


void stackAssert(stack *stk)
{
    errorCode error = verify(stk);
    if (error)
    {
        logStack(stk, LOG_ERROR);
        loggerDeinit();
        DBG(printError(error);)
        assert(0);
    }
}

void printError(errorCode error)
{
    switch (error)
    {
        case STK_OK:
            break;
        case STK_STRUCT_NULL_POINTER:
            fprintf(stderr, "STK_STRUCT_NULL_POINTER\n");
            break;
        case STK_OUT_MEMORY:
            fprintf(stderr, "STK_OUT_MEMORY\n");
            break;
        case STK_SIZE_LARGER_CAPACITY:
            fprintf(stderr, "STK_SIZE_LARGER_CAPACITY\n");
            break;
        case BAD_SIZE:
            fprintf(stderr, "BAD_SIZE\n");
            break;
        case STK_CAPACITY_NOT_EXSIST:
            fprintf(stderr, "STK_CAPACITY_NOT_EXSIST\n");
            break;
        default:
            fprintf(stderr, "unknow mistake :)\n");
    }

}
