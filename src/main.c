#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

#define SIZE 1024

typedef struct var
{
    char* varName;
    char* varVal;
} VAR;

typedef struct data
{
    char* eq;
    VAR* variables;
    int varCount;
} DATA;

int priority(int c)
{
    switch (c)
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

void clear(char* str)
{
    for (int i = strlen(str); i >= 0; --i)
    {
        str[i] = '\0';
    }
}

int makeData(DATA* data, FILE* in)
{
    int pos = 0;
    while (!feof(in))
    {
        char* str = calloc(SIZE, sizeof(char));
        fgets(data[pos].eq, SIZE, in);
        clear(str);
        int varPos = 0;
        while (!feof(in))
        {
            fgets(str, SIZE, in);
            if (strlen(str) == 1)
            {
                break;
            }
            sscanf(str, "%s = %s", data[pos].variables[varPos].varName, data[pos].variables[varPos].varVal);
            clear(str);
            varPos++;
        }
        data[pos].varCount = varPos;
        pos++;
        varPos = 0;
        free(str);
    }
    return pos;
}

int main()
{
    FILE* in = fopen("../data/input.txt", "r");
    FILE* out = fopen("../data/output.txt", "w");
    DATA* data = calloc(SIZE, sizeof(DATA));
    for (int i = 0; i < SIZE; ++i)
    {
        data[i].eq = calloc(SIZE, sizeof(char));
        data[i].variables = calloc(SIZE, sizeof(VAR));
        for (int j = 0; j < SIZE; ++j)
        {
            data[i].variables[j].varName = calloc(SIZE, sizeof(char));
            data[i].variables[j].varVal = calloc(SIZE, sizeof(char));
        }
    }
    int dataAmount = makeData(data, in);

    for (int inputCount = 0; inputCount < dataAmount; ++inputCount)
    {
        char* math = calloc(SIZE, sizeof(char));
        char* pol = calloc(SIZE, sizeof(char));
        char* nums = calloc(SIZE, sizeof(char));
        double* ans = calloc(SIZE, sizeof(char));
        STACK opr;

        memset(opr.data, 0, sizeof(SIZE_STACK));
        opr.pos = 0;
        int pos = 0;

        strcpy(math, data[inputCount].eq);

        ////<------------------POLISH NOTATION------------------>////

        for (int i = 0; i < strlen(math); ++i)
        {
            if (math[i] >= '0' && math[i] <= '9' || math[i] >= 'a' && math[i] <= 'z' || math[i] == '.' ||
                math[i] == '-' && math[i - 1] == ' ')
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
            if (pol[pos - 1] != ' ')
            {
                pol[pos++] = ' ';
            }
            pol[pos++] = peek(&opr);
            if (pol[pos - 1] != ' ')
            {
                pol[pos++] = ' ';
            }
            pop(&opr);
        }

        pos = 0;
        int subPos = 0;

        ////<--------------------CALCULATION-------------------->////

        for (int i = 0; i < strlen(pol) - 1; ++i)
        {
            if (pol[i] >= '0' && pol[i] <= '9' || pol[i] >= 'a' && pol[i] <= 'z' || pol[i] == '.' ||
                pol[i] == '-' && pol[i + 1] != ' ')
            {
                nums[pos++] = pol[i];
            }
            for (int check = 0; check < data[inputCount].varCount; ++check)
            {
                if (!strcmp(data[inputCount].variables[check].varName, nums))
                {
                    clear(nums);
                    strcpy(nums, data[inputCount].variables[check].varVal);
                    break;
                }
            }
            if (pol[i] == ' ' && pol[i - 1] != '+' && pol[i - 1] != '-' && pol[i - 1] != '*' && pol[i - 1] != '/' &&
                pol[i - 1] != '^')
            {
                ans[subPos++] = atof(nums);
                clear(nums);
                pos = 0;
            }
            if (pol[i] == '+' || pol[i] == '-' && pol[i + 1] == ' ' || pol[i] == '*' || pol[i] == '/' || pol[i] == '^')
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
                        if (ans[subPos - 1] == 0)
                        {
                            break;
                        }
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
        if (subPos != 1)
        {
            fprintf(out, "%d) Error: division by zero\n", inputCount + 1);
        }
        else
        {
            fprintf(out, "%d) %.10f\n", inputCount + 1, ans[0]);
        }

        free(math);
        free(pol);
        free(nums);
        free(ans);
    }
    fclose(in);
    fclose(out);
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            free(data[i].variables[j].varName);
            free(data[i].variables[j].varVal);
        }
        free(data[i].eq);
        free(data[i].variables);
    }
    free(data);
    printf("Done");
    return 0;
}
