#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "logger.h"
#include "color.h"
#include "debug.h"


static const size_t capacity_multiplier = 2;


errorCode stackCtor(stack *stk, ssize_t capacity)
{
    stkNullCheck(stk);
    stk->capacity = capacity;

    if (stk->capacity <= 0)
    {
        DBG_FPRINTF(stderr, COLOR_RED "ERROR: BAD CAPACITY = %zd\n" COLOR_RESET, stk->capacity);
        assert(0);
    }

    stk->data = (stackElem*)calloc((size_t)capacity + 2, sizeof(stackElem));
    if (stk->data == NULL)
    {
        fprintf(stderr, "memory allocation error\n");
        return STK_OUT_MEMORY;
    }
    DBG_PRINTF(COLOR_MAGENTA"Start: stk->data = %p\n" COLOR_RESET, stk->data);

    stk->size = 0;
    DBG_PRINTF(COLOR_MAGENTA "Start: stk->size = %zd\n" COLOR_RESET, stk->size);

    canary(stk);

    DBG_PRINTF(COLOR_MAGENTA"Start: stk->capacity = %zd\n\n" COLOR_RESET, stk->capacity);
    stackAssert(stk);

    return STK_OK;
}

errorCode stackReallocUp(stack *stk)
{
    stackAssert(stk);
    stackElem *stk_tmptr = (stackElem*)realloc(stk->data, ((size_t)stk->capacity * capacity_multiplier + 2) * sizeof(stackElem));
    if (stk_tmptr == NULL)
    {
        fprintf(stderr, "Realloc allocate failed\n");
        return STK_REALLOC_FAILED;
    }
    stk->data = stk_tmptr;
    stk->capacity *= (ssize_t)capacity_multiplier;

    canary(stk);
    stackAssert(stk);
    return STK_OK;
}


errorCode stackPush(stack *stk, stackElem elem)
{
    DBG_PRINTF(COLOR_CYAN "Push " STACK_ELEM_FORMAT " elem to stack\n" COLOR_RESET, elem);
    stackAssert(stk);

    if (stk->size >= stk->capacity)
        stackReallocUp(stk);

    stk->data[stk->size + 1] = elem;
    DBG_PRINTF(COLOR_YELLOW "Stack after push stk->data[%zd] = " STACK_ELEM_FORMAT "\n" COLOR_RESET, stk->size, elem);
    stk->size++;

    stackAssert(stk);
    return STK_OK;
}

errorCode stackReallocDown(stack *stk)
{
    stackAssert(stk);
    stackElem *stk_tmptr = (stackElem*)realloc(stk->data, ((size_t)stk->capacity / capacity_multiplier + 2) * sizeof(stackElem));
    if (stk_tmptr == NULL)
    {
        fprintf(stderr, "Realloc allocate failed\n");
        return STK_REALLOC_FAILED;
    }
    stk->data = stk_tmptr;
    stk->capacity /= (ssize_t)capacity_multiplier;

    canary(stk);
    //stk->data[0] = 1;
    stackAssert(stk);
    return STK_OK;
}

errorCode stackPop(stack *stk, stackElem *elem_from_stack)
{
    stackAssert(stk);
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POISON;

    if ((stk->size >= 5) && (stk->size <= stk->capacity / 4))
        stackReallocDown(stk);

    stackAssert(stk);
    return STK_OK;
}

errorCode stackReallocToFree(stack *stk)
{
    if (stk->size == 0)
    {
        stackElem *stk_tmptr = (stackElem*)realloc(stk->data, 3 * sizeof(stackElem));
        if (stk_tmptr == NULL)
        {
            fprintf(stderr, "Realloc allocate failed\n");
            return STK_REALLOC_FAILED;
        }
        stk->data = stk_tmptr;
        stk->capacity = 1;

        canary(stk);
        stackAssert(stk);
        return STK_OK;
    }
    return CANT_REALLOC_TO_FREE;
}

errorCode stackDtor(stack *stk)
{
    stkNullCheck(stk);
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;

    DBG_PRINTF(COLOR_MAGENTA"Finished: stk->data = %p\n" COLOR_RESET, stk->data);
    DBG_PRINTF(COLOR_MAGENTA"Capacity: %zd\n" COLOR_RESET, stk->capacity);
    DBG_PRINTF(COLOR_MAGENTA"Size: %zd\n" COLOR_RESET, stk->size);
    DBG_PRINTF(COLOR_MAGENTA"Data pointer: %p\n" COLOR_RESET, stk->data);

    return STK_OK;
}


