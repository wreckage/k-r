/* K&R - Combines exercises 3-4 and 3-6:
 *
 * Exercise 3-4. In a two's complement number representation, 
 * our version of itoa does not handle the largest negative number, 
 * that is, the value of n equal to -(2wordsize-1). Explain why 
 * not. Modify it to print that value correctly, regardless 
 * of the machine on which it runs.  
 *
 * Exercise 3-6. Write a version of itoa that accepts 
 * three arguments instead of two. The third argument is a 
 * minimum field width; the converted number must be padded 
 * with blanks on the left if necessary to make it wide enough.  */


#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 100

void reverse(char s[]);
void itoa(int n, char s[], int f);

/* reverse: reverse a string in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int f)
{
    int i, j, sign, diff;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        printf("n is: %d\n", n);
        printf("ssss: %d\n", (s[i++] = abs(n % 10) + '0'));
    } while (n /= 10);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    diff = f - strlen(s);
    printf("diff: %d %d %d\n", diff, f, strlen(s));
    if (diff > 0) {
        for (j = 0; j < diff; j++)
            s[i++] = '0';
        s[i] = '\0';
    }
    reverse(s);
}

int main(void)
{
    char s[MAX];
    int i, n, f;
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);

    f = 6;
    
    n = 2000000;
    itoa(n, s, f);
    printf("With n as %d and field %d: %s\n", n, f, s);
    n = 2000;
    itoa(n, s, f);
    printf("With n as %d and field %d: %s\n", n, f, s);
    return 0;
}
