/* K&R - Exercise 6-2. Write a program that reads a C program and prints in 
 * alphabetical order each group of variable names that are identical 
 * in the first 6 characters, but different somewhere thereafter. 
 * Don't count words within strings and comments. Make 6 a parameter that 
 * can be set from the command line. */

/* This was a very challenging program to create. It makes use of strtok, but
 * since the standard library has already been mentioned, I don't think its
 * use keeps this from being a category 0 solution. I tested it with a few
 * different C programs and it works ok, but there are likely still some
 * bugs here and there.
 *
 * Here's how the program is supposed to work:
 * First we grab variable names and add them to a binary tree, where if 
 * given something like:
 *
 * int x, myvar = 2, y;
 *
 * then the variables are x, myvar, and y.
 * Then we print the ones that are the same for the first n characters, 
 * but different somewhere thereafter, where n is 6 by default but can 
 * be set from the command line. When n = 1 (i.e. the program is run 
 * with the '-1' option), the program prints all of the variables found, 
 * along with how many of each were found (this is similar to the example
 * program in chapter 6-2).  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXLINE 1000
#define NTYPES (sizeof type / sizeof *type)

#define GOODTOKEN(s) (binsearch(s, type, NTYPES) < 0 && strlen(s)) ? 1 : 0

char *type[] = {
    "char",
    "enum",
    "float",
    "int",
    "long",
    "short",
    "struct",
    "void",
};

struct tnode { /*the tree node */
    char *word; /* points to itself */
    int count; /* number of occurences */
    struct tnode *left; /* left child */
    struct tnode *right; /* right child */
};

int getline_(char *, char *, int);
void *getvarfromtoken(char *, char *, int);
int goodtoken(char *);
char *moveforward(char *, int);
int binsearch(char *, char **, int);

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
void treeprint(struct tnode *, int);
char *strdupli(char *s);
int wegood(char *, char *, int);


int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char line[MAXLINE];
    char word[MAXWORD];
    char var[MAXWORD];
    char s[MAXWORD];
    char *token;
    char *p;
    int i = 0, skipfirst = 0;
    int match_num; /* words that match first match_num, diff elsewhere */

    while (--argc > 0 && (*++argv)[0] == '-')
        while (isdigit(*++argv[0]))
            s[i++] = *argv[0];

    s[i] = '\0';

    match_num = strlen(s) ? atoi(s) : 6;

    while (getline_(line, word, MAXLINE) > 0)
        for (i = 0; i < NTYPES; i++)
            if (strcmp(word, type[i]) == 0) {
                if (strcmp(type[i], "struct") == 0)
                    skipfirst = 1;
                p = moveforward(line, strlen(type[i]));
                token = strtok(p, ", ");
                while (token) {
                    if (!skipfirst) {
                        getvarfromtoken(token, var, MAXWORD);
                        if (GOODTOKEN(var))
                            root = addtree(root, var);
                    }
                    else
                        skipfirst = 0;
                    token = strtok(NULL, ",");
                }
            }
    treeprint(root, match_num);
    return 0;
}

/* moveforward: return 's', which is 'p' moved forward by 'len' amount */
char *moveforward(char *p, int len)
{
    int i = 0;
    char *s = p;

    for (i = 0; i < len; i++)
        s++;
    return s;
}

/* getline_: read a line into 'line', first word of line into 'w' */
int getline_(char *line, char *w, int lim)
{
    int c, space = 0;
    char *s = line;

    while (isspace(c=getchar()))
        ;
    if (c != EOF)
        *line++ = c;

    while (--lim > 0 && (c=getchar()) != EOF && c != '\n') {
        if (isspace(c) && space == 0) {
            space = 1;
            *line = '\0';
            strcpy(w, s);
        }
        *line++ = c;
    }
    if (c == '\n')
        *line++ = c;
    *line = '\0';
    if (!space)
        *w = '\0';
    return (line - s > 0) ? 1 : 0;
}

/* getvar: get variable name from token */
void *getvarfromtoken(char *token, char *var, int lim)
{
    char c;

    while(isspace(c=*token++))
        ;
    if (isalpha(c))
        *var++ = c;
    else if (!(isalpha(c)) && c != '*') {
        *var = '\0';
        return NULL;
    }

    while (!isspace(c=*token++) && c != '(' && c != ')' && c != '[' && c != ';')
        *var++ = c;

    *var = '\0';
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, char *tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, tab[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else {
            return mid;
        }
    }
    return -1;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) { /* a new word has arrived*/
        p = talloc(); /* make a new node */
        p->word = strdupli(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond=strcmp(w, p->word))==0)
        p->count++;
    else if (cond < 0)
    {
        p->left = addtree (p->left, w);
    } else
    {
        p->right = addtree(p->right, w);
    }
    return p;
}

void treeprint (struct tnode *p, int match_num)
{
    static char *pw = NULL;  /* previous word encountered */
    static char match = 0;  /* 0 for no match, 1 for match */
    char *w;  /* used to create a shorthand for p->word */

    if (p != NULL) {
        w = p->word;
        treeprint(p->left, match_num);
        if (pw != NULL && match_num != 1) {
            if (wegood(pw, w, match_num))
            {
                /* We need match to tell us if this is our first match.
                 * If it is, we print the previous word and current word.
                 * Otherwise, we only print the current word. */
                if (!match) {
                    match = 1;
                    printf("%s\n%s\n", pw, w);
                } else {
                    printf("%s\n", w);
                }
            } 
            else {
                match = 0;
                pw = w;
            }
        }
        else if (match_num == 1)
           printf("%4d %s\n", p->count, p->word); 
        else {
            pw = w;
        }
        treeprint(p->right, match_num);
    }
}

/* wegood: check that 'pw' & 'w' are the same for the first 'm' characters,
 * but different somewhere after.  */
int wegood(char *pw, char *w, int m)
{
    if (strlen(pw) > m && strncmp(pw, w, m) == 0 && 
            strncmp(pw, w, strlen(pw)) != 0) 
        return 1;
    else
        return 0;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char *strdupli(char *s)
{
    char *p;
    p = (char *) malloc (strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}
