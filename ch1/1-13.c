/* K&R - Exercise 1-13. Write a program to print a histogram of the 
 * lengths of words in its input. It is easy to draw the histogram 
 * with the bars horizontal; a vertical orientation is more challenging.  */

#include <stdio.h>

// max height of histogram
#define MAX 10

main() {
    int i, j, c, state, nc;
    int nw[10];

    nc = 0;

    for (i = 0; i < 10; i++) 
        nw[i] = 0;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == ' ' || c == '\n' || c == '\t') {
            ++nw[nc];
            nc = 0;
        }
    }
    for (i = 0; i < 10; i++) {
        printf("%d: ", i);
        for (j = 0; j < nw[i]; j++)
            printf("*");
        printf("\n");
    }
}
