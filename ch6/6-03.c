/* K&R - Exercise 6-3. Write a cross-referencer that prints a 
 * list of all words in a document, and for each word, a list of the 
 * line numbers on which it occurs. Remove noise words like 'the',
 * 'and', and so on.  */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXNUMS 1000
#define MAXLINES 10000
#define NNOISE (sizeof(noisewords) / sizeof(*noisewords))

/* word not in noisewords */
#define SEARCH(word)((binsearch(word, noisewords, NNOISE)) == -1)

#define LEN(word)(strlen(word) > 1)  /* avoid single character words */
#define ALPHA(word)(isalpha(word[0]))
#define GOOD(word)(ALPHA(word) && SEARCH(word) && LEN(word))

int nlines = 0;

struct tnode {
    char *word;
    int linenums[MAXNUMS];  /* line numbers on which 'word' appears */
    int f;  /* #elements in linenums */
    struct tnode *left;
    struct tnode *right;
};

char *noisewords[] = {
    "and",  
    "as", 
    "at",
    "because",
    "but",
    "for",
    "has",
    "if",
    "in",
    "into",
    "is",
    "of",
    "on",
    "or", 
    "so",
    "the",
    "to",
    "too",
    "with"
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdupl(char *);
int getword(char *, int);
int binsearch(char *, char **, int);

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (GOOD(word))
            root = addtree(root, word);
    printf("LINE #     WORD\n");
    printf("----------------\n");
    treeprint(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdupl(w);
        p->f = 0;
        p->linenums[p->f++] = nlines;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->linenums[p->f++] = nlines;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void treeprint(struct tnode *p)
{
    int i;
    if (p != NULL) {
        treeprint(p->left);
        for (i = 0; i < p->f; i++)
            printf("%4d %10s\n", p->linenums[i] + 1, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdupl(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            if (nlines < MAXLINES)
                nlines++;
            else {
                printf("Error: too many lines");
                exit(1);
            }


    if (c != EOF) {
        *w++ = c;
    }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return *word;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int binsearch(char *word, char *list[], int n)
{
    int cond;
    int low, mid, high;
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, list[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else 
            return mid;
    }
    return -1;
}
