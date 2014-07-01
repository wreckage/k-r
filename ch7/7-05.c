/* K&R - Exercise 7-5. Rewrite the postfix calculator of Chapter 4 
 * to use scanf and/or sscanf to do the input and number conversion.  */

/* Thanks to Toni Romic for the idea of catching the character after 
 * the string in scanf. This lets us know if we encounter a newline, 
 * in which case we should print the answer. 
 * See his solution here:
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_7:Exercise_5
 */

#include <stdio.h>
#include <stdlib.h>  /* for atof */
#include <math.h>  /* for fmod */

#define MAXSTACK 100

double stack[MAXSTACK];
int sp = 0;

double pop(void)
{
    if (sp > 0)
        return stack[--sp];
    else {
        printf("stack empty\n");
        return 0.0;
    }
}

void push(double num)
{
    if (sp < MAXSTACK)
        stack[sp++] = num;
    else
        printf("error: stack full, can't push %.2f\n", num);
}

int main(void)
{
    char s[100], i, end;
    double num, op2;

    end = '\0';

    while(scanf("%s%c", s, &end) == 2) {
        if ((num = atof(s)) != 0)
            push(num);
        else {
            for (i = 0; s[i]; i++)
                switch (s[i]) {
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
                    default:
                        printf("error: unknown command: %s\n", s);
                        break;
                }
            if (end == '\n') {
                end = '\0';
                printf("\t%.8g\n", pop());
            }
        }
    }
    return 0;
}
