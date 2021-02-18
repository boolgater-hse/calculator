#pragma once
#define SIZE 101

typedef struct _stack
{
    char data[SIZE];
    int pos;
} STACK;

void push(STACK* stack, char value);
char pop(STACK* stack);
char peek(STACK* stack);
int isEmpty(STACK* stack);
