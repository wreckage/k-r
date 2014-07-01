/* Exercise 7-3. Revise minprintf to handle more of the other facilities 
 * of printf.  */

/* Added pointer display with %p and allow spaces to be set with num
 * before letter, e.g. %5s */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;  /* points to each unnamed arg in turn */
    char *p, *sval;
    void *vp;
    int ival, col = 0;
    double dval;

    va_start(ap, fmt);  /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        /* set col if any digits */
        while (isdigit(*++p)) {
            col = col * 10 + (*p - '0');
            if (col >= 40)  /* allow up to 40 spaces */
                col = 0;
        }

        switch (*p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%*d", col, ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%*f", col, dval);
                break;
            case 's':
                while (col--)
                    printf(" ");
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case 'p':
                vp = va_arg(ap, void *);
                printf("%*p", col, vp);
                break;
            default:
                putchar(*p);
                break;
        }
        col = 0;
    }
    va_end(ap);  /* clean up when done */
}

int sum(int num_args, ...)
{
    int val = 0;
    va_list ap;
    int i;

    va_start(ap, num_args);

    for (i = 0; i < num_args; i++)
        val += va_arg(ap, int);

    va_end(ap);
    return val;
}

int main(void)
{
    char s[] = "Hello World!";
    minprintf("I say, %s\n", s);
    minprintf("Here's a character: %c\n", 'z');

    printf("Sum of 2, 5, and 22 is: %d\n", sum(3, 2, 5, 22));

    char *p;
    minprintf("A character pointer's address: %p\n", p);

    int *ip;
    minprintf("An int pointer's address: %p\n", ip);
    printf("\nWith spaces:\n");
    minprintf("An int: %19d and a string: %10s\n", 100, "a string");

    return 0;
}
