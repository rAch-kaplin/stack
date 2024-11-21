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
        assert(0);
    }
}
