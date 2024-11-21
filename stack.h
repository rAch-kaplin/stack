#ifndef _HSTACK
#define _HSTACK

typedef int stackElement;
const stackElement POISON = 0xBAD1ABA;
#define STACK_ELEM_FORMAT "%d"

enum errorCode
{
    STK_OK = 0,
    STK_OUT_MEMORY = 1,
    STK_REALLOC_FAILED = 2,
    STK_EMPTY_STACK = 3,
    STK_SIZE_LARGER_CAPACITY = 4,
    STK_CAPACITY_NOT_EXSIST = 5,
    BAD_CAPACITY = 6,
    BAD_SIZE = 7,
    STK_STRUCT_NULL_POINTER = 8,
    FILE_POINTER_IS_NULL = 9
};

struct stack
{
    stackElement *data;
    ssize_t size;
    size_t capacity;
};


errorCode stackCtor(stack *stk, size_t capacity);
errorCode stackPush(stack *stk, stackElement elem);
errorCode stackDtor(stack *stk);
errorCode stackPop(stack *stk, stackElement *elem_from_stack);


#endif
