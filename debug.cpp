#include <assert.h>
#include "debug.h"


errorCode verify(const stack *stk)
{
    errorCode error = STK_OK;

    if (stk == NULL)
        error = STK_STRUCT_NULL_POINTER;

    if (stk->data == NULL)
        error = STK_OUT_MEMORY;

    if (stk->size > stk->capacity)
        error = STK_SIZE_LARGER_CAPACITY;
    // if (stk->size < 0)
    //     error = BAD_SIZE;

    if (stk->capacity == 0)
        error = STK_CAPACITY_NOT_EXSIST;

    // if (stk->capacity < 0)
    //     error = BAD_CAPACITY;

    return error;
}


void stackAssert(stack *stk)
{
    errorCode error = verify(stk);
    if (error)
    {
        logStack(stk, LOG_ERROR);
        assert(0);
    }

}
