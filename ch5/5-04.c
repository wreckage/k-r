/* K&R - Exercise 5-4. Write the function strend(s, t), which returns 1 if the
 * string occurs at the end of the string s, and 0 otherwise. */

/* see 
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_5:Exercise_4
 * for a much more efficient solution: Unlike my solution that goes through
 * the entire s string, it goes straight to where the comparison
 * needs to be made. */

#include <stdio.h>
#include <string.h>
#define MATCH "match"
#define NOMATCH "no match"
#define CHECK(r) r ? MATCH : NOMATCH

/* strend(s, t): returns 1 if t occurs at the end of s, 0 otherwise */
int strend(char *s, char *t)
{
    int i, count;

    i = count = 0;
    
    while(*s)
        if (*s++ == t[i++])
            count++;
        else
            i = count = 0;

    return (count > 0 && strlen(t) == count) ? 1 : 0;
}

main(void)
{
    int result1, result2, result3;

    char s1[] = "hello world";
    char s2[] = "world";

    char s3[] = "hello world";
    char s4[] = "";

    char s5[] = "hello world";
    char s6[] = "hell ld";

    result1 = strend(s1, s2);
    result2 = strend(s3, s4);
    result3 = strend(s5, s6);

    printf("result1: %d (%s)\n", result1, CHECK(result1));
    printf("result2: %d (%s)\n", result2, CHECK(result2));
    printf("result3: %d (%s)\n", result3, CHECK(result3));

    return 0;
}
