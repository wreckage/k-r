/* K&R - Exercise 2-4. Write an alternative version of 
 * squeeze(s1,s2) that deletes each character in 
 * s1 that matches any character in the string s2.  */

/* came close to solving this one but couldn't quite do it.
 * As it is now, this program simply replaces vowels in s[]
 * with empty spaces.
 * Finally just had to look up the solution.  */

#include <stdio.h>
#define MAXLINE 1000

void squeeze(char s[], char c[]);
int getline(char s[], int lim);


/* squeeze: delete all c from s */
void squeeze(char s[], char s2[]) {
    int i, j, k, b;

    b = 0;
    /* This for loop should be switched w/ the inner for loop! */
    for (k = 0; s2[k] != '\0'; k++) {
        for (i = j = 0; s[i] != '\0'; i++) {
            if (s[i] != s2[k])
                s[j++] = s[i];
            else
                s[j++] = ' ';
            /*
            else
                b++;
            */
        }
    }
    /*
    s[j - b] = '\0';
    */
}


/* getline: read a line into s, return length */
int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    /* count the newline character so that even blank lines 
     * have at least len 1 */
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0'; /* Add the null character to the end of the line */
    return i;
}


int main(void) {
    int len; /* current line length */
    char line[MAXLINE]; /* current input line */
    char vowels[10];
    vowels[0] = 'a';
    vowels[1] = 'e';
    vowels[2] = 'i';
    vowels[3] = 'o';
    vowels[4] = 'u';
    vowels[5] = 'A';
    vowels[6] = 'E';
    vowels[7] = 'I';
    vowels[8] = 'O';
    vowels[9] = 'U';
    vowels[10] = '\0';

    while ((len = getline(line, MAXLINE)) > 0) {
        squeeze(line, vowels);
        printf("%s", line);
    }
    return 0;
}

