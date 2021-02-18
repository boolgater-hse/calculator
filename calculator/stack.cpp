#include "stack.h"

void push(STACK* stack, char value)
{
    stack->data[stack->pos] = value;
    stack->pos++;
}

char pop(STACK* stack)
{
    if (stack->pos == 0) return -1;
    stack->pos--;
    return stack->data[stack->pos];
}

char peek(STACK* stack)
{
    if (stack->pos == 0) return;
    return stack->data[stack->pos - 1];
}

int isEmpty(STACK* stack)
{
    if (stack->pos == 0) return 1;
    else return 0;
}
