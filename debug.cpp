#include "debug.h"
#include "color.h"


int canary(stack *stk)
{
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}


int verify(const stack *stk)
{
    int error = 0;

    if (stk == NULL)
    {
        error = error | STK_STRUCT_NULL_POINTER;
        return error;
    }

    if (stk->data == NULL)
        error = error | STK_OUT_MEMORY;
    else
    {
        if (stk->data[0] != CANARY)
            error = error | BAD_CANARY_1;

        if (stk->data[stk->capacity + 1] != CANARY)
            error = error | BAD_CANARY_2;
    }

    if ((size_t)stk->size > stk->capacity)
        error = error | STK_SIZE_LARGER_CAPACITY;

    if (stk->size < 0)
        error = error | BAD_SIZE;

    if (stk->capacity == 0)
        error = error | STK_CAPACITY_NOT_EXSIST;


    return error;
}


void stackAssert(stack *stk)
{
    int error = verify(stk);
    if (error)
    {
        logStack(stk, LOG_ERROR);
        loggerDeinit();
        DBG(decoderError(stderr, error);)
        assert(0);
    }
}

int decoderError(FILE * fp_error, int error)
{
    if (error & STK_STRUCT_NULL_POINTER)
        DBG_FPRINTF(fp_error, COLOR_RED"STK_STRUCT_NULL_POINTER\n" COLOR_RESET);

    if (error & STK_OUT_MEMORY)
        DBG_FPRINTF(fp_error, COLOR_RED"STK_OUT_MEMORY\n" COLOR_RESET);

    if (error & STK_SIZE_LARGER_CAPACITY)
        DBG_FPRINTF(fp_error, COLOR_RED"STK_SIZE_LARGER_CAPACITY\n" COLOR_RESET);

    if (error & BAD_SIZE)
        DBG_FPRINTF(fp_error,COLOR_RED "BAD_SIZE\n" COLOR_RESET);

    if (error & STK_CAPACITY_NOT_EXSIST)
        DBG_FPRINTF(fp_error, COLOR_RED"STK_CAPACITY_NOT_EXSIST\n" COLOR_RESET);

    if (error & BAD_CANARY_1)
        DBG_FPRINTF(fp_error, COLOR_RED"BAD_CANARY_1\n" COLOR_RESET);

    if (error & BAD_CANARY_2)
        DBG_FPRINTF(fp_error,COLOR_RED "BAD_CANARY_2\n" COLOR_RESET);

    return error;
}
