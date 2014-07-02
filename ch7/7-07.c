/* K&R - Exercise 7-7. Modify the pattern finding program of 
 * Chapter 5 to take its input from a set of named files or, 
 * if no files are named as arguments, from the standard input. 
 * Should the file name be printed when a matching line is found?  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
#define MAXCHAR 50

static char except = 0, number = 0;

struct file {
    FILE *fp;
    char *filename;
};

int main(int argc, char *argv[])
{
    struct file *f;
    char pattern[MAXCHAR], *prog = argv[0];
    int c, found = 0, search(char *pattern, struct file *);

    f = malloc(sizeof(struct file));

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch(c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    fprintf(stderr, "%s: illegal option %c\n", prog, c);
                    exit(-1);
            }
    if (argc == 0) {
        fprintf(stderr, "Usage: %s -x -n pattern file(s)\n", prog);
        exit(1);
    }
    strncpy(pattern, *argv, MAXCHAR);
    if (argc == 1) {  /* no files specified, so use stdin */
        f->fp = stdin;
        f->filename = NULL;
        found += search(pattern, f);
    }
    else
        while (--argc > 0)
            if ((f->fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                f->filename = *argv;
                found += search(pattern, f);
                fclose(f->fp);
            }
    return found;
}

int search(char *pattern, struct file *f)
{
    char line[MAXLINE];
    long lineno = 0;
    int found = 0;

    while (fgets(line, MAXLINE, f->fp) != NULL) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except) {
            if (f->filename != NULL)
                printf("%s: ", f->filename);
            if (number)
                printf("%1d: ", lineno);
            printf("%s", line);
            found++;
        }
    }
    return found;
}
