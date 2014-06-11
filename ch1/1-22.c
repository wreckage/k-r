/* K&R - Exercise 1-22. Write a program to ''fold'' long input lines 
 * into two or more shorter lines after the last non-blank 
 * character that occurs before the n-th column of input. 
 * Make sure your program does something intelligent with very 
 * long lines, and if there are no blanks or tabs 
 * before the specified column.  */

#include <stdio.h>
#define MAXCHARS 20 /* break the line at MAXCHARS */
#define TABSTOP 4 /* number of spaces in a tabstop */

int main(void) {
    int c, len;

    len = 0;

    while((c = getchar()) != EOF) {
        len++;
        /* add the appropriate number to len when a tab is encountered */
        if (c == '\t')
            /* subtract 1 b/c len was already incremented once */
            len = len + TABSTOP - 1;
        if (len == MAXCHARS) {
            len = 0;
            putchar('\n');
        }
        else if (c == '\n')
            len = 0;
        putchar(c);
    }
    return 0;
}
