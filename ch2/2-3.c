/* K&R - Exercise 2-3. Write a function htoi(s), which converts 
 * a string of hexadecimal digits (including an optional 0x or 0X) 
 * into its equivalent integer value. The allowable digits are 0 
 * through 9, a through f, and A through F.  */

/* XXX Not printing single digits correctly! */

#include <stdio.h>
#include <math.h>

#define MAX 1000

double atoi(char s[]);
short err = 0;

double atoi(char s[]) {
    extern short err;
    int i, n;

    n = 0;

    for (i = 0; i < MAX && s[i] != '\0'; i++) 
        if (s[i] >= '0' && s[i] <= '9')
            n = n + ((s[i] - '0') * pow(16, i));
        else if (s[i] >= 'A' && s[i] <= 'F')
            n = n + (((s[i] - 'A') + 10) * pow(16, i));
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = n + (((s[i] - 'a') + 10) * pow(16, i));
        else
            err = 1;

    return n;
}

int main(void) {
    extern short err;
    char s[MAX];
    char s2[MAX];
    int c, i, j;
    double result;

    i = j = 0;

    while (i < MAX - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    i--;
    /* invert the char array */
    while (i >= 0)
        s2[j++] = s[i--];

    s2[j] = '\0';

    result = atoi(s2);

    if (err)
        printf("Invalid digit detected.\n");
    else
        printf("Hexadecimal %s to decimal is: %.0f\n", s, result);

    return 0;
}
