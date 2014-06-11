/* K&R - This combines many of the exercises from chapter 4.3 */

/* Thanks to Pilcrow for the nopprint idea. See: 
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_4
 */
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h> /* for fmod */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
double show(void);
void dup(void);
void switcheroo(void);
void clear(void);

/* reverse Polish calculator */


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

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;      /* not a number or negative sign */
    i = 0;
    if (isdigit(c) || c == '-')    /* collect the integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')      /* collect the fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int show_buf(void)
{
    printf("buf: %s\n", buf);
    printf("bufp: %d\n", bufp);
}
int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
