/* K&R - Exercise 1-9. Write a program to copy its input to its output, 
 * replacing each string of one or more blanks by a single blank.  */

#include <stdio.h>

main() {
    int c, b;
    
    b = 0;
    
    while((c = getchar()) != EOF) {
        if (c == ' ')
            b++;
        else
            b = 0;

        if (b < 2) {
            if (c == '\t')
                printf("%s", "\\t");
            else
                putchar(c);
        }
    }
}
