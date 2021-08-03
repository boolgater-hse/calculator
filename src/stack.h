#pragma once
#define SIZE_STACK 20

typedef struct _stack
{
    char data[SIZE_STACK];
    int pos;
} STACK;

void push(STACK* stack, char value);
char pop(STACK* stack);
char peek(STACK* stack);
int isEmpty(STACK* stack);
