/* Exercise 5-10. Write the program expr, which evaluates a reverse
 * Polish expression from the command line, where each operator or
 * operand is a separate arument. For example,
 *
 * expr 2 3 4 + *
 *
 * evaluates 2 * (3+4). 
 *
 * Currently only supports +/- but can be easily extended. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define NUMBER '0'

void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    double op;
    char *s, *type, err = 0;

    if (argc == 1) {
        printf("Usage: expr <numbers> <operators>\n");
        return 1;
    }

    while(--argc > 0) {
        s = *++argv;
        if (isdigit(*s))
            *type = NUMBER;
        else
            *type = *s;

        switch(*type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op = pop();
                push(pop() - op);
                break;
            default:
                printf("expr: invald argument\n");
                err = 1;
                break;
        }
    }
    if (err)
        return 1;
    else
        printf("\t%.8g\n",pop());

    return 0;
}

#define MAXVAL 100

int stack = 0;
double val[MAXVAL];


void push(double f)
{
    if (stack < MAXVAL)
        val[stack++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
    return;
}

double pop(void)
{
    if (stack > 0) return val[--stack];
    else {
        printf("stack empty\n");
        return 0;
    }
}
