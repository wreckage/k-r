/* K&R - Exercise 5-5. Write versions of the library functions 
 * strncpy, strncat, and strncmp, which operate on at most the 
 * first n characters of their argument strings. For example, 
 * strncpy(s,t,n) copies at most n characters of t to s. 
 * Full descriptions are in Appendix B.  */

/* This one is for strncpy */

#include <stdio.h>
#define MAX 10000
#define STRMATCH 4

void mystrncpy(char *s, char *t, int n);

/* strncpy: copy at most n characters of t to s */
void mystrncpy(char *s, char *t, int n)
{
    int i;

    for (i = 0; i < n && *t; i++)
        *s++ = *t++;
}

main(void)
{
    char s2[MAX];
    char s[MAX] = "hello world!";

    mystrncpy(s2, s, STRMATCH);
    printf("Original string: %s\n", s);
    printf("Copied string: %s\n", s2);
    return 0;
}
