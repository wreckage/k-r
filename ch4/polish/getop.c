/* Exercise 4-11. Modify getop so that it doesn't 
 * need to use ungetch. Hint: use an internal
 * static variable. */

#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define BUFSIZE 100

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    static int buf = EOF;

    /* if/else to check if anything was in buf */
    if (buf != EOF) {
        s[0] = c = buf;
        buf = EOF;
        while (c == ' ' || c == '\t')
            s[0] = c = getch();
    }
    else
        while ((s[0] = c = getch()) == ' ' || c == '\t')
            ;

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
        buf = c;
    return NUMBER;
}
