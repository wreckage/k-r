/* K&R - Exercise 3-3
 * Write a function expand(s1,s2) that expands shorthand notations 
 * like a-z in the string s1 into the equivalent complete list abc...xyz in s2. 
 * Allow for letters of either case and digits, and be prepared to handle cases 
 * like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is 
 * taken literally.
 */

/* This program could be improved by checking for mismatched characters/digits
 * e.g. a-D and 0-q should respond with a-D and 0-q, respectively.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

void expand(char s1[], char s2[])
{
    int i, j, k, len, start, end, diff;
    len = strlen(s1);

    for (i = j = 0; i < len; i++)
        if (s1[i] != '-')
            s2[j++] = s1[i];
        else {
            if (i == 0 || i == len - 1 || s1[i+1] == ' ')
                s2[j++] = s1[i]; /* interpret the dash literally */
            else {
                start = s1[i-1];
                end = s1[i+1];
                diff = (end-start);
                if (diff > 0)
                    /* something like a-c or 1-4: expand normally */
                    for (k = 1; k < diff && diff > 1; k++)
                        s2[j++] = start + k;
                else if (diff < 0)
                    /* something like c-a or 4-1: expand in reverse */
                    for (k = 1; k < abs(diff) && abs(diff) > 1; k++)
                        s2[j++] = start - k;
                else
                    /* something like a-a: interpret literally */
                    s2[j++] = s1[i];
            }
        }
    s2[j] = '\0';
}

int main(void)
{
    int i;
    char s[] = "-Testa-zcool-";
    char ss[MAXLINE];
    char s3[] = "9-0a-b- c-g a-a F-Q";
    char s4[MAXLINE];

    expand(s, ss);
    printf("This: %s\nExpands to this: %s\n", s, ss);

    expand(s3, s4);
    printf("This: %s\nExpands to this: %s\n", s3, s4);
    return 0;
}
