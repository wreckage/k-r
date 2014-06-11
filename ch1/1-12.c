/* Exercise 1-12. Write a program that prints its input one word per line.  */

#include <stdio.h>

#define IN 1
#define OUT 0

main() {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ' | c == '\n' | c == '\t')
            printf("\n");
        else
            putchar(c);
    }
}
