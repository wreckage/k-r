/* k&r - exercise 1-19  */
/* Write a function reverse(s) that reverses the character string s. Use it to
 * write a program that reverses its input a line at a time. */

#include <stdio.h>
#define MAX 1000

int reverse(char s[]);

main() {
    int len;
    char line[MAX];

    while((len = reverse(line)) > 0)
        printf("%s\n", line);
    return 0;
}

/* reverse: reverses the order of a given string array. returns length. */
int reverse(char s[]) {
    int i, j, c;
    char temp[MAX];

    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
        temp[i] = c;
    for (j = 0; j < i; j++) {
        s[j] = temp[i-j-1];
    }
    if (c == '\n') {
        s[i] = '\n';
        ++i;
    }
    s[i] = '\0';
    return i;
}
