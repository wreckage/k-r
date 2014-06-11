#include <stdio.h>
#include "calc.h"

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* show: print the top elements of the stack without popping */
double show(void)
{
    if (!sp)
        printf("stack is empty\n");
    else {
        int sp2 = sp;

        while(sp2)
            printf("*** %.8g\n", val[--sp2]);
    }
}

/* dup: duplicate the top element on the stack */
void dup(void)
{

    if (!sp)
        printf("stack is empty\n");
    else  {
        val[sp++] = val[sp - 1];
        printf("top stack element %.8g has been duplicated\n", val[sp - 1]);
    }
}

/* switcheroo: swap the top two elements */
void switcheroo(void)
{
    if (sp < 2)
        printf("not enough elements on the stack to perform a swap\n");
    else {
        double v = val[sp - 2];
        val[sp - 2] = val[--sp];
        val[sp++] = v;
        printf("switched the valued %.8g and %.8g\n", val[sp - 2], v);
    }
}

/* clear: clear the stack */
void clear(void)
{
    sp = 0;
    printf("the stack has been cleared\n");
}
