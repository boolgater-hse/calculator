#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

#define SIZE 101

typedef struct var
{
    char varName[SIZE];
    char varVal[SIZE];
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

int makeData(DATA data[], FILE* in)
{
    int pos = 0;
    while (!feof(in))
    {
        char str[SIZE] = { 0 };
        fgets(data[pos].eq, SIZE, in);
        clear(str);
        int varPos = 0;
        while (!feof(in))
        {
            fgets(str, SIZE, in);
            if (strlen(str) == 1) break;
            sscanf(str, "%s = %s\n", &data[pos].variables[varPos].varName, &data[pos].variables[varPos].varVal);
            clear(str);
            varPos++;
        }
        data[pos].varCount = varPos;
        pos++;
        varPos = 0;
    }
    return pos;
}

void clear(char* str)
{
    for (int i = strlen(str); i >= 0; --i)
    {
        str[i] = '\0';
    }
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    DATA data[SIZE];
    int dataAmount = makeData(data, in);
    fclose(in);

    ////<--------------------POLISH-------------------->////

    for (int inputCount = 0; inputCount < dataAmount; ++inputCount)
    {
        char math[SIZE] = { 0 }, pol[SIZE] = { 0 };
        char nums[SIZE] = { 0 };
        double ans[SIZE] = { 0 };
        STACK opr;
        memset(opr.data, 0, sizeof(SIZE));
        opr.pos = 0;
        int pos = 0;

        strcpy(data[inputCount].eq, math);
        printf("%d) ", inputCount + 1);
        
        for (int i = 0; i < strlen(math); ++i)
        {
            if (math[i] >= '0' && math[i] <= '9' || math[i] >= 'a' && math[i] <= 'z' || math[i] == '.' || math[i] == '-' && math[i - 1] == ' ')
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
    }
}