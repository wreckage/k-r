/* Exercise 2-5. Write the function any(s1,s2), 
 * which returns the first location in a string s1 
 * where any character from the string s2 occurs, 
 * or -1 if s1 contains no characters from s2. 
 * (The standard library function strpbrk does the 
 * same job but returns a pointer to the 
 * location.)  */

#include <stdio.h>

#define MAX 1000

int any(char s1[], char s2[]);

int any(char s1[], char s2[]) {
    int i, j;
    signed int fail;

    fail = -1;

    for (i = 0; s1[i] != '\0'; i++)
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j]) {
                return i;
            }
    return fail;
}

/* OLD - realized that a flag is unneccessary.. can just return!
int any(char s1[], char s2[]) {
    signed int location;
    int i, j, flag;

    location = -1;
    flag = 0;

    for (i = 0; s1[i] != '\0' && !flag; i++)
        for (j = 0; s2[j] != '\0' && !flag; j++)
            if (s1[i] == s2[j]) {
                location = i;
                flag = 1;
            }
    return location;
}
*/
int main(void) {
    char q1[MAX] = "Hello world!";
    char q2[MAX] = "zwh";
    signed int location;

    location = any(q1, q2);
    printf("%d\n", location);

    return 0;
}
