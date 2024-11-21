#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "logger.h"
#include "color.h"
#include "debug.h"


static const size_t capacity_multiplier = 2;


errorCode stackCtor(stack *stk, size_t capacity)
{
    stk->data = (stackElement*)calloc(capacity, sizeof(stackElement));
    if (stk->data == NULL)
    {
        fprintf(stderr, "memory allocation error\n");
        return STK_OUT_MEMORY;
    }
    DBG_PRINTF("Start: stk->data = %p\n", stk->data);

    stk->size = 0;
    DBG_PRINTF("Start: stk->size = %zd\n", stk->size);

    stk->capacity = capacity;
    DBG_PRINTF("Start: stk->capacity = %zu\n\n", stk->capacity);
    stackAssert(stk);

    return STK_OK;
}

errorCode stackReallocUp(stack *stk)
{
        stackElement *stk_tmptr = (stackElement*)realloc(stk->data, stk->capacity * capacity_multiplier * sizeof(stackElement));
        if (stk_tmptr == NULL)
        {
            fprintf(stderr, "Realloc allocate failed\n");
            return STK_REALLOC_FAILED;
        }
        stk->data = stk_tmptr;
        stk->capacity *= capacity_multiplier;
        return STK_OK;
}


errorCode stackPush(stack *stk, stackElement elem)
{
    DBG_PRINTF(COLOR_CYAN "Push " STACK_ELEM_FORMAT " elem to stack\n" COLOR_RESET, elem);
    stackAssert(stk);

    if ((size_t)stk->size >= stk->capacity)
        stackReallocUp(stk);

    stk->data[stk->size] = elem;
    DBG_PRINTF(COLOR_YELLOW "Stack after push stk->data[%zd] = " STACK_ELEM_FORMAT "\n" COLOR_RESET, stk->size, elem);
    stk->size++;


    stackAssert(stk);
    return STK_OK;
}

errorCode stackReallocDown(stack *stk)
{
        stackElement *stk_tmptr = (stackElement*)realloc(stk->data, (stk->capacity / capacity_multiplier) * sizeof(stackElement));
        if (stk_tmptr == NULL)
        {
            fprintf(stderr, "Realloc allocate failed\n");
            return STK_REALLOC_FAILED;
        }
        stk->data = stk_tmptr;
        stk->capacity /= capacity_multiplier;
        return STK_OK;
}

errorCode stackPop(stack *stk, stackElement *elem_from_stack)
{
    stackAssert(stk);
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->data[stk->size];
    stk->data[stk->size] = POISON;

    if ((stk->size >= 5) && ((size_t)stk->size <= stk->capacity / 4))
        stackReallocDown(stk);


    stackAssert(stk);
    return STK_OK;
}

errorCode stackReallocToFree(stack *stk)
{
    if (stk->size == 0)
    {
        stackElement *stk_tmptr = (stackElement*)realloc(stk->data, 1 * sizeof(stackElement));
        if (stk_tmptr == NULL)
        {
            fprintf(stderr, "Realloc allocate failed\n");
            return STK_REALLOC_FAILED;
        }
        stk->data = stk_tmptr;
        stk->capacity = 1;
        return STK_OK;
    }
    return CANT_REALLOC_TO_FREE;
}

errorCode stackDtor(stack *stk)
{
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    return STK_OK;
}


