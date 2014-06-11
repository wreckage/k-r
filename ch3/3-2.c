/* K&R - Exercise 3-2. Write a function escape(s,t) that converts 
 * characters like newline and tab into visible escape sequences 
 * like \n and \t as it copies the string t to s. 
 * Use a switch. Write a function for the other direction as well, 
 * converting escape sequences into the real characters.  */

#include <stdio.h>

#define MAXCHARS 1000

void escape(char s[], char t[]);

/* escape: copies the string t to s while coverting character to visible
 * escape sequences. */
void escape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0' && i < MAXCHARS; i++, j++)
        switch (t[i]) {
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            /* and so on... */
            default:
                s[j] = t[i];
                break;
        }
    s[j] = t[i]; /* null character */
}

int main(void) {

    char s[MAXCHARS];
    char t[] = "G'day\tmate!\n";

    escape(s, t);
    printf("String 1:\n%s\n", t);
    printf("String 2:\n%s\n", s);
    return 0;
}
