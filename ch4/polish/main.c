#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100 /* max size of operand or operator */

main()
{
    int type;
    int nopprint = 0;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case '$':
                nopprint = 1;
                show_buf();
                break;
            case '?':
                nopprint = 1;
                show();
                break;
            case '#':
                nopprint = 1;
                dup();
                break;
            case '~':
                nopprint = 1;
                switcheroo();
                break;
            case '!':
                nopprint = 1;
                clear();
                break;
            case '\n':
                if (nopprint)
                    nopprint = 0;
                else
                    printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
