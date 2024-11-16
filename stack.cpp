#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "logger.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

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

static const size_t capacity_multiplier = 2;


int main()
{
    loggerInit("stack.log", "stack_error.log");

    struct stack stk = {NULL, 0, 0};
    //createFile(&stk);
    //DBG(dump(&stk);)

    stackElement elem_from_stack = 0; //TODO: StackElem

    stackCtor(&stk, 5);
    //DBG(dump(&stk);)
    logStack(&stk, LOG_INFO);

    for (int i = 0; i < 10; i++)
    {
        stackPush(&stk, (i + 1) * 10);
        logStack(&stk, LOG_INFO);
        //DBG(dump(&stk);)
    }

    while(stk.size > 0)
    {
        stackPop(&stk, &elem_from_stack);
        printf(COLOR_GREEN "elem_from_stack = " STACK_ELEM_FORMAT " \n\n" COLOR_RESET, elem_from_stack);
        logStack(&stk, LOG_INFO);
        //DBG(dump(&stk);)
    }

    stackDtor(&stk);
    //DBG(dump(&stk);)
    logStack(&stk, LOG_INFO);
    DBG_PRINTF("Finished: stk->data = %p\n", stk.data);

    loggerDeinit();
    //fclose(stk.fp);
    return 0;
}

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
    DBG_PRINTF("Start: stk->size = %zu\n", stk->size);

    stk->capacity = capacity;
    DBG_PRINTF("Start: stk->capacity = %zu\n\n", stk->capacity);
    DBG(stackAssert(stk);)

    return STK_OK;
}

errorCode stackPush(stack *stk, stackElement elem)
{
    DBG_PRINTF(COLOR_CYAN "Push " STACK_ELEM_FORMAT " elem to stack\n" COLOR_RESET, elem);
    DBG(stackAssert(stk);)

    if (stk->size >= stk->capacity)
    {
        stackElement *stk_tmptr = (stackElement*)realloc(stk->data, stk->capacity * capacity_multiplier * sizeof(stackElement));
        if (stk_tmptr == NULL)
        {
            fprintf(stderr, "Realloc allocate failed\n");
            return STK_REALLOC_FAILED;
        }
        stk->data = stk_tmptr;
        stk->capacity *= capacity_multiplier;
    }

    stk->data[stk->size] = elem;
    DBG_PRINTF(COLOR_YELLOW "Stack after push stk->data[%zu] = " STACK_ELEM_FORMAT "\n" COLOR_RESET, stk->size, elem);

    stk->size++;
    DBG(stackAssert(stk);)
    return STK_OK;
}

errorCode stackPop(stack *stk, stackElement *elem_from_stack)
{
    DBG(stackAssert(stk);)
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->data[stk->size];
    stk->data[stk->size] = POISON;

    DBG(stackAssert(stk);)
    return STK_OK;
}


errorCode stackDtor(stack *stk)
{
    //fclose(stk->fp);
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    return STK_OK;
}

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

// errorCode createFile(stack *stk)
// {
//     FILE *fp = fopen("StackLOGFile.txt", "w+");
//     if (fp == NULL)
//     {
//         fprintf(stderr, "Can't open the file\n");
//         return FILE_POINTER_IS_NULL;
//     }
//
//     stk->fp = fp;
//     fprintf(stderr, COLOR_CYAN "In createFile fp = %p\n" COLOR_RESET, fp);
//     return STK_OK;
// }

#if 0
errorCode dump(stack *stk)
{
    FILE *fp = stk->fp;
    if (fp == NULL)
    {
        fprintf(stderr, COLOR_RED "File pointer is NULL in dump\n" COLOR_RESET);
        return FILE_POINTER_IS_NULL;
    }

    DBG_FPRINTF_NO_ARGS(fp, "\t\tSTACK:\n");
    for (size_t i = 0; i < stk->capacity; i++)
    {
        DBG_FPRINTF(fp, STACK_ELEM_FORMAT " ", stk->data[i]);
    }

    DBG_FPRINTF_NO_ARGS(fp, "\n//==================================\n");

    DBG_FPRINTF_NO_ARGS(fp, "\t\tStruct:\n");
    DBG_FPRINTF(fp, "-data = %p\n", stk->data);
    DBG_FPRINTF(fp, "-size = %zu\n", stk->size);
    DBG_FPRINTF(fp, "-capacity = %zu\n", stk->capacity);

    //puts("\n");

    return STK_OK;
}
#endif

void stackAssert(stack *stk)
{
    errorCode error = verify(stk);
    if (error)
    {
        logStack(stk, LOG_ERROR);
        assert(0);
    }

}
