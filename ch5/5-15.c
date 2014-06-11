/* Exercise 5-14. Modify the sort program to handle a -r flag, 
 * which indicates sorting in reverse (decreasing) order. 
 * Be sure that -r works with -n.  */

/* Exercise 5-15. Add the option -f to fold upper and lower case together, 
 * so that case distinctions are not made during sorting; for example, 
 * a and A compare equal.    */


#include <stdio.h>
#include <string.h>


#define MAXLEN 1000  /* max length of any input line */

int getline_(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline_(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len-1] = '\0';  /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getline:  read a line into s, return length  */
int getline_(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */
   
char *alloc(int n)    /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n)  /* it fits */
    {
        allocp += n;
        return allocp - n;  /* old p */
    } 
    else     /* not enough room */
        return 0;
}


#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort_(void *lineptr[], int left, int right,
        int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);
int istrcmp(char *, char *);


/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;       /* number of input lines read */
    int numeric = 0;  /* 1 if numeric sort */
    int reverse = 0;  /* 1 if reverse order */
    int fold = 0;  /* 1 if fold upper & lower cases */
    int (*func)(void*, void*);
    char c;

    while (--argc > 0 && (*++argv)[0] == '-')
        while(c = *++argv[0])
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'f':
                fold = 1;
                break;
            default:
                printf("Error: Invalid Option %c\n", c);
                break;
            }

    if (numeric) {
        func = (int (*)(void*, void*))(numcmp);
    }
    else if (fold) {
        func = (int (*)(void*, void*))(istrcmp);
    }
    else {
        func = (int (*)(void*,void*))(strcmp);
    }
                
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_((void**) lineptr, 0, nlines-1, func, reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort_(void *v[], int left, int right,
        int(*comp)(void *, void *), int reverse)
{
    int i, last;

    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (reverse) {
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
        } else {
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_(v, left, last-1, comp, reverse);   /* sort the two */
    qsort_(v, last+1, right, comp, reverse);  /* sublists */
}

#include <ctype.h>

/* istrcmp: compare lexicographically, ignoring case. */
int istrcmp(char *s1, char *s2)
{
    for ( ; tolower(*s1) == tolower(*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return tolower(*s1) - tolower(*s2);
}
    
#include <stdlib.h>

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

