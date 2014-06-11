/* Exercise 5-7. Rewrite readlines to store lines in an array 
 * supplied by main, rather than calling alloc to maintain storage. 
 * How much faster is the program? */

/* No idea how much faster it is not using alloc.*/

/* NOTE: getline() is a standard lib func defined in stdio.h
 * In order to run this program correctly, must either change the name
 * of getline() or compile using -ansi option */


#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
#define MAXSTORAGE 10000     /* max storage space */

char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char s[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);


/* sort input lines */
main()
{
    char s[MAXSTORAGE];
    int nlines; /* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES, s)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int getline(char *, int);
char *alloc(int);


/* getline: read a line into s, return length */
int getline(char s[], int lim) {
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
    while((len = getline(line, MAXLEN)) > 0) {
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
void writelines(char *lineptr[], int nlines)
{
    int i;

    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}


/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)  /* do nothing if array contains */ 
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}


/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
