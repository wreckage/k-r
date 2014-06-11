/* K&R - Exercise 5-3. Write a pointer version of the function strcat
 * that we showed in Chapter 2: strcat(s, t) copies the string t
 * to the end of s */

#include <stdio.h>

#define MAX 10000

/* ostrcat: The old version of strcat from chapter 2 */
void ostrcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0') /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0') /* copy t */
        ;
}

/* strcat: copy the string t to the end of s; pointer version */
void pstrcat(char *s, char *t)
{
    while (*s)
        s++;
    while (*s++ = *t++)
        ;
}

main(void)
{
    char mssg1[MAX] = "hello";
    char mssg2[MAX] = " world!";

    printf("mssg1: %s\n", mssg1);
    printf("mssg2: %s\n", mssg2);
    pstrcat(mssg1, mssg2);
    printf("mssg1 after cat: %s\n", mssg1);

    return 0;
}
