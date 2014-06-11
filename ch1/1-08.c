/* K&R - Exercise 1-8. Write a program to count blanks, tabs, and newlines. */

#include <stdio.h>

main() {
    int c, nl, t, b;
    
    nl = t = b = 0;

    while((c = getchar()) != EOF) {
        if (c == '\n')
            nl++;
        if (c == '\t')
            t++;
        if (c == ' ')
            b++;
    }
    printf("Counted:\n%d newlines\n%d tabs\n%d blanks\n", nl, t, b);
}
