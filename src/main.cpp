#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "logger.h"
#include "color.h"
#include "debug.h"


int main()
{
    loggerInit(LOGL_DEBUG, "stack.log");

    struct stack stk = {NULL, 0, 0};

    stackElem elem_from_stack = 0;

    stackCtor(&stk, 5);
    LOG(LOGL_DEBUG, "STACK Ctor:\n", &stk);

    for (int i = 0; i < 11; i++)
    {
        stackPush(&stk, (i + 1) * 10);
        LOG(LOGL_DEBUG, "STACK PUSH: %d\n", &stk, stk.data[i + 1]);
        // stk.data[5] = 10000;
    }
    // stk.size = 17;
    while(stk.size > 0)
    {
        stackPop(&stk, &elem_from_stack);
        printf(COLOR_GREEN "elem_from_stack = " STACK_ELEM_FORMAT " \n\n" COLOR_RESET, elem_from_stack);
        LOG(LOGL_DEBUG, "STACK POP: %d\n", &stk, elem_from_stack);
    }
    capacityOptimization(&stk);
    LOG(LOGL_DEBUG, "Optimization capacity:\n", &stk);

    stackDtor(&stk);

    loggerDeinit();
    return 0;
}
