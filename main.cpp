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
    LOG(LOGL_DEBUG, "STACK DUMP:", &stk);

    for (int i = 0; i < 11; i++)
    {
        stackPush(&stk, (i + 1) * 10);
        LOG(LOGL_DEBUG, "STACK DUMP:", &stk);
    }

    while(stk.size > 0)
    {
        stackPop(&stk, &elem_from_stack);
        printf(COLOR_GREEN "elem_from_stack = " STACK_ELEM_FORMAT " \n\n" COLOR_RESET, elem_from_stack);
        LOG(LOGL_DEBUG, "STACK DUMP:", &stk);
    }
    stackReallocToFree(&stk);
    LOG(LOGL_DEBUG, "STACK DUMP:", &stk);

    stackDtor(&stk);

    loggerDeinit();
    return 0;
}
