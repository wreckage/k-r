/* K&R - Exercise 4-13. Write a recursive version of the 
 * function reverse(s), which reverses the
 * string s in place. */

#include <stdio.h>
#include <string.h>

void r_reverse(char []);
void reverse(char []);

/* r_reverse: reverse a string in place, recursively */
void r_reverse(char s[])
{
    static int i = 0;
    static int j = 1;
    int c;
    int end = (strlen(s) - j++);

    if (i < end) {
        c = s[i];
        s[i++] = s[end];
        s[end] = c;
        r_reverse(s);
    }
    else {        /* reset the variables when we're done */
        i = 0;
        j = 1;
    }
}



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

main(void)
{
    char s3[] = "niaga siht esrever";
    char s2[] = "siht esrever";
    char s1[] = "siht esrever";
    printf("Old string: %s\n", s1);
    reverse(s1);
    printf("Reversed string: %s\n", s1);
    r_reverse(s2);
    printf("Reversed string with recursion: %s\n", s2);
    r_reverse(s3);
    printf("Reversed string with recursion: %s\n", s3);
}
