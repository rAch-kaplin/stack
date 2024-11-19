#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "logger.h"
#include "color.h"
#include "debug.h"
// TODO: reallocDown()

int main()
{
    loggerInit("stack.log", "stack_error.log");

    struct stack stk = {NULL, 0, 0};


    stackElement elem_from_stack = 0; //TODO: StackElem

    stackCtor(&stk, 5);
    logStack(&stk, LOG_INFO);

    for (int i = 0; i < 10; i++)
    {
        stackPush(&stk, (i + 1) * 10);
        logStack(&stk, LOG_INFO);
    }

    while(stk.size > 0)
    {
        stackPop(&stk, &elem_from_stack);
        printf(COLOR_GREEN "elem_from_stack = " STACK_ELEM_FORMAT " \n\n" COLOR_RESET, elem_from_stack);
        logStack(&stk, LOG_INFO);
    }

    stackDtor(&stk);
    logStack(&stk, LOG_INFO);
    DBG_PRINTF("Finished: stk->data = %p\n", stk.data);

    loggerDeinit();
    return 0;
}