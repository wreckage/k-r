/* K&R - Exercise 7-1. Write a program that converts upper case to 
 * lower or lower case to upper, depending on the name it is 
 * invoked with, as found in argv[0].  */

/* This program makes use of bit-fields, as covered in section 6.9. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct {
    unsigned int use_upper : 1;
    unsigned int use_lower : 1;
} flags;

int main(int argc, char **argv)
{
    char c;

    if (strstr(argv[0], "upper") != NULL) {
        flags.use_upper = 1;
        flags.use_lower = 0;
    } else if (strstr(argv[0], "lower") != NULL) {
        flags.use_upper = 0;
        flags.use_lower = 1;
    } else {
        printf("Error: must be compiled into a file called ");
        printf("'upper' or 'lower'. \nRecompile and try again.\n");
        exit(1);
    }

    if (flags.use_upper)
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    else if (flags.use_lower)
        while ((c = getchar()) != EOF)
            putchar(tolower(c));

    return 0;
}

