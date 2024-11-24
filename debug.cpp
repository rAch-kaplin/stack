#include "debug.h"
#include "color.h"
#include "logger.h"


int canary(stack *stk)
{
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}

void stkNullCheck(const stack *stk)
{
    if (stk == NULL)
    {
        DBG_FPRINTF(stderr, COLOR_RED "ERROR: STK POINTER IS NULL\n" COLOR_RESET);
        assert(0);
    }
}


int verify(stack *stk)
{
    int error = 0;
    stkNullCheck(stk);

    if (stk->data == NULL)
        error = error | STK_OUT_MEMORY;
    else
    {
        if (stk->data[0] != CANARY)
            error = error | BAD_CANARY_1;

        if (stk->data[stk->capacity + 1] != CANARY)
            error = error | BAD_CANARY_2;
    }

    if (stk->size > stk->capacity)
        error = error | STK_SIZE_LARGER_CAPACITY;

    if (stk->size < 0)
        error = error | BAD_SIZE;

    if (stk->capacity <= 0)
        error = error | STK_CAPACITY_NOT_EXSIST;


    return error;
}


void stackAssert(stack *stk)
{
    int error = verify(stk);
    if (error)
    {
        LOG(LOGL_ERROR, "Stack verification failed: %s\n", decoderError(error));
        loggerDeinit();
        //decoderError(stderr, error);
        assert(0);
    }
}

const char* decoderError(int error)
{
    if (error & STK_STRUCT_NULL_POINTER)
    {
        //DBG_FPRINTF(fp_error, COLOR_RED"STK_STRUCT_NULL_POINTER\n" COLOR_RESET);
        return "STK_STRUCT_NULL_POINTER";
    }

    if (error & STK_OUT_MEMORY)
    {
        //DBG_FPRINTF(fp_error, COLOR_RED"STK_OUT_MEMORY\n" COLOR_RESET);
        return "STK_OUT_MEMORY";
    }

    if (error & STK_SIZE_LARGER_CAPACITY)
    {
        //DBG_FPRINTF(fp_error, COLOR_RED"STK_SIZE_LARGER_CAPACITY\n" COLOR_RESET);
        return "STK_SIZE_LARGER_CAPACITY";
    }

    if (error & BAD_SIZE)
    {
        //DBG_FPRINTF(fp_error,COLOR_RED "BAD_SIZE\n" COLOR_RESET);
        return "BAD_SIZE";
    }

    if (error & STK_CAPACITY_NOT_EXSIST)
    {
        //DBG_FPRINTF(fp_error, COLOR_RED"STK_CAPACITY_NOT_EXSIST\n" COLOR_RESET);
        return "STK_CAPACITY_NOT_EXSIST";
    }

    if (error & BAD_CANARY_1)
    {
        //DBG_FPRINTF(fp_error, COLOR_RED"BAD_CANARY_1\n" COLOR_RESET);
        return "BAD_CANARY_1";
    }

    if (error & BAD_CANARY_2)
    {
        //DBG_FPRINTF(fp_error,COLOR_RED "BAD_CANARY_2\n" COLOR_RESET);
        return "BAD_CANARY_2";
    }

    return "Unknow Error :(";
}
