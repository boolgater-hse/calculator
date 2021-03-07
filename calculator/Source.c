#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

#define SIZE 101

typedef struct var
{
    char varName[SIZE];
    double varVal;
} VAR;

typedef struct data
{
    char eq[SIZE];
    VAR variables[SIZE];
    int varCount;
} DATA;

int priority(int symb)
{
    switch (symb)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return 0;
}

//int toNum(char* str)
//{
//    int ret = 0, mult, count = 0;
//    mult = strlen(str) - 1;
//    for (int i = 0; i < strlen(str); i++)
//    {
//        ret = ret + (str[i] - '0') * pow(10, mult);
//        mult--;
//    }
//    for (int i = strlen(str); i >= 0; --i)
//    {
//        str[i] = '\0';
//    }
//    return ret;
//}

void clear(char* str)
{
    for (int i = strlen(str); i >= 0; --i)
    {
        str[i] = '\0';
    }
}

int main()
{
    char math[SIZE] = { 0 }, pol[SIZE] = { 0 };
    STACK opr; // STACK
    memset(opr.data, 0, sizeof(SIZE));
    opr.pos = 0;
    char nums[SIZE] = { 0 };
    double ans[SIZE] = { 0 };
    int pos = 0;
    fgets(math, SIZE, stdin);
    printf("Expression:\n");
    printf("%s\n", math);
    printf("Reverse Polish Notation:\n");

    ////<--------------------POLISH-------------------->////
   
    for (int i = 0; i < strlen(math); ++i)
    {
        if (math[i] >= '0' && math[i] <= '9' || math[i] >= 'a' && math[i] <= 'z' || math[i] == '.' || math[i] == '-'&& math[i-1] == ' ')
        {
            pol[pos++] = math[i];
            continue;
        }
        if (math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/' || math[i] == '^')
        {
            if (pol[pos - 1] != ' ')
            {
                pol[pos++] = ' ';
            }
            if (isEmpty(&opr))
            {
                push(&opr, math[i]);
            }
            else if (priority(math[i]) > priority(peek(&opr)) || priority(math[i]) == 3)
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
            if (pol[pos - 1] != ' ')
            {
                pol[pos++] = ' ';
            }
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

    //exit(0);

    ////<--------------------CALCULATION-------------------->////

    for (int i = 0; i < strlen(pol) - 1; ++i)
    {
        if (pol[i] >= '0' && pol[i] <= '9' || pol[i] == '.' || pol[i] == '-' && pol[i+1] != ' ')
        {
            nums[pos++] = pol[i];
        }
        if (pol[i] == ' ' && pol[i - 1] != '+' && pol[i - 1] != '-' && pol[i - 1] != '*' && pol[i - 1] != '/' && pol[i - 1] != '*')
        {
            ans[subPos++] = atof(nums);
            clear(nums);
            pos = 0;
        }
        if (pol[i] == '+' || pol[i] == '-' && pol[i+1] == ' ' || pol[i] == '*' || pol[i] == '/' || pol[i] == '^')
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
            case '^':
                ans[subPos - 2] = pow(ans[subPos - 2], ans[subPos - 1]);
                subPos--;
                break;
            }
        }
    }
    if (subPos == 0)
    {
        ans[subPos++] = atof(nums);
        clear(nums);
        pos = 0;
    }
    printf("%.4f", ans[0]);
}
