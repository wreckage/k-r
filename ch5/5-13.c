/* K&R - Exercise 5-13. Write the program tail, which prints 
 * the last n lines of its input. By default, n is set 
 * to 10, let us say, but it can be changed by an 
 * optional argument so that  
 *
 * tail -n 
 * prints the last n lines. The program should behave 
 * rationally no matter how unreasonable the input or 
 * the value of n. Write the program so it makes the 
 * best use of available storage; lines should be 
 * stored as in the sorting program of Section 5.6, 
 * not in a two-dimensional array of fixed size.  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 10000     /* max #lines */
#define MAXSTORAGE 10000     /* max storage space */

char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char s[]);
void writelines(char *lineptr[], int nlines, int show_lines);
int getline_(char *, int);


/* sort input lines */
int main(int argc, char *argv[])
{
    char s[MAXSTORAGE];
    char s2[MAXSTORAGE]; /* array w/ # lines to show */
    int nlines;          /* number of input lines read */
    int show_lines;      /* number of lines to print */
    int i = 0;

    /* get # lines to show from argv, if specified */
    while (--argc > 0 && (*++argv)[0] == '-')
        while (isdigit(*++argv[0]))
            s2[i++] = *argv[0];

    s2[i] = '\0';

    show_lines = strlen(s2) ? atoi(s2) : 10;

    if ((nlines = readlines(lineptr, MAXLINES, s)) >= 0) {
        writelines(lineptr, nlines, show_lines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}


/* getline: read a line into s, return length */
int getline_(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    /* count the newline character so that even blank lines 
     * have at least len 1 */
    if (c == '\n') {
        for (; s[i-1] == ' ' || s[i-1] == '\t'; --i)
            ;
        s[i] = c;
        ++i;
    }
    s[i] = '\0'; /* Add the null character to the end of the line */
    return i;
}


#define MAXLEN  1000  /* max length of any input line */

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *s)
{
    int len, nlines, total;
    char line[MAXLEN];

    nlines = total = 0;
    while((len = getline_(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (total + len) > MAXSTORAGE)
            return -1;
        else {
            line[len-1] = '\0';  /* delete newline */
            strcpy(s, line);
            lineptr[nlines++] = s;
            s += len;
            total += len;
        }
    }
    return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int show_lines)
{
    int i;

    while (nlines-- > 0)
        if (nlines < show_lines)
            printf("%s\n", *lineptr++);
        else  /* remove this else to create the program 'head' */
            lineptr++;
}
