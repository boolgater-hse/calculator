#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

#define SIZE 101

// Ilya Sergeevich, have a great day!
// Hello

////<--------------------STACK FUNCS-------------------->////

int priority(int symb)
{
    switch (symb)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    }
    return 0;
}

int toNum(char* str)
{
    int ret = 0, mult, count = 0;
    mult = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        ret = ret + (str[i] - '0') * pow(10, mult);
        mult--;
    }
    for (int i = strlen(str); i >= 0; --i)
    {
        str[i] = '\0';
    }
    return ret;
}

int main()
{
    char math[SIZE] = { 0 }, pol[SIZE] = { 0 };
    STACK opr; // STACK
    opr.pos = 0;
    char nums[SIZE] = { 0 };
    int ans[SIZE] = { 0 };
    int pos = 0;
    fgets(math, SIZE, stdin);
    printf("Expression:\n");
    printf("%s\n", math);
    printf("Reverse Polish Notation:\n");

    ////<--------------------POLISH-------------------->////

    for (int i = 0; i < strlen(math); ++i)
    {
        if (math[i] >= '0' && math[i] <= '9')
        {
            pol[pos++] = math[i];
        }
        if (math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/')
        {
            if (pol[pos - 1] != ' ')
            {
                pol[pos++] = ' ';
            }
            if (isEmpty(&opr))
            {
                push(&opr, math[i]);
            }
            else if (priority(math[i]) > priority(peek(&opr)))
            {
                push(&opr, math[i]);
            }
            else if (priority(math[i]) <= priority(peek(&opr)))
            {
                while (priority(math[i]) <= priority(peek(&opr)) && !(isEmpty(&opr)))
                {
                    pol[pos++] = peek(&opr);
                    pol[pos++] = ' ';
                    pop(&opr);
                }
                push(&opr, math[i]);
            }
        }
        if (math[i] == '(')
        {
            if (pos == 0)
            {
                push(&opr, math[i]);
            }
            else
            {
                if (pol[pos - 1] != ' ')
                {
                    pol[pos++] = ' ';
                }
                push(&opr, math[i]);
            }
        }
        if (math[i] == ')')
        {
            pol[pos++] = ' ';
            while (peek(&opr) != '(')
            {
                pol[pos++] = peek(&opr);
                pol[pos++] = ' ';
                pop(&opr);
            }
            pop(&opr);
        }
        if (math[i + 1] == '\0' || math[i + 1] == '\n')
        {
            if (pol[pos - 1] != ' ')
            {
                pol[pos++] = ' ';
            }
        }
    }
    while (!(isEmpty(&opr)))
    {
        pol[pos++] = peek(&opr);
        if (pol[pos - 1] != ' ')
        {
            pol[pos++] = ' ';
        }
        pop(&opr);
    }
    printf("%s\n", pol);

    printf("Result:\n");

    pos = 0;
    int subPos = 0;

    ////<--------------------CALCULATION-------------------->////

    for (int i = 0; i < strlen(pol) - 1; ++i)
    {
        if (pol[i] >= '0' && pol[i] <= '9')
        {
            nums[pos++] = pol[i];
        }
        if (pol[i] == ' ' && pol[i - 1] != '+' && pol[i - 1] != '-' && pol[i - 1] != '*' && pol[i - 1] != '/')
        {
            ans[subPos++] = toNum(nums);
            pos = 0;
        }
        if (pol[i] != '+' || pol[i] != '-' || pol[i] != '*' || pol[i] != '/')
        {
            switch (pol[i])
            {
            case '+':
                ans[subPos - 2] = ans[subPos - 2] + ans[subPos - 1];
                subPos--;
                break;
            case '-':
                ans[subPos - 2] = ans[subPos - 2] - ans[subPos - 1];
                subPos--;
                break;
            case '*':
                ans[subPos - 2] = ans[subPos - 2] * ans[subPos - 1];
                subPos--;
                break;
            case '/':
                ans[subPos - 2] = ans[subPos - 2] / ans[subPos - 1];
                subPos--;
                break;
            }
        }
    }
    if (subPos == 0)
    {
        ans[subPos++] = toNum(nums);
        pos = 0;
    }
    printf("%d", ans[0]);
}