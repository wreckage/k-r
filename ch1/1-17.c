/* K&R - Exercise 1-17. Write a program to print all input lines 
 * that are longer than 80 characters.  */

/* NOTE getline() is a standard lib func defined in stdio.h
 * In order to run this correctly, must either change the name
 * of getline() or compile using -ansi option */

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);

/* print the longest input line */
main() {
    int len; /* current line length */
    int max; /* maximum length seen so far */
    char line[MAXLINE]; /* current input line */

    max = 80;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len > max) {
            printf("line with %d lines:\n", len);
            printf("%s", line);
        }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    /* count the newline character so that even blank lines 
     * have at least len 1 */
    if (c == '\n') {
        for (; s[i-1] == ' ' || s[i-1] == '\t'; --i)
            ;
        s[i] = c;
        ++i;
    }
    s[i] = '\0'; /* Add the null character to the end of the line */
    return i;
}
