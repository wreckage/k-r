/* K&R - Exercise 7-6. Write a program to compare two files, 
 * printing the first line where they differ.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096    /* maximum line length */
#define MAXLINES 10000  /* max total lines */

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE], *c1, *c2;
    char *prog = argv[0];
    int nlines = 1;
    
    if (argc != 3) {
        fprintf(stderr, "%s usage: %s <file1> <file2>\n", prog, prog);
        exit(1);
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL) {  /* Open the first file */
        fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
        exit(1);
    }

    if ((fp2 = fopen(argv[2], "r")) == NULL) {  /* Open the second file */
        fprintf(stderr, "%s: can't open %s\n", prog, argv[2]);
        exit(1);
    }

    while ((c1 = fgets(line1, MAXLINE, fp1)),
            (c2 = fgets(line2, MAXLINE, fp2))) {
        /* If we reach EOF, or if the lines aren't equal, break */
        if (c1 == NULL || c2 == NULL || strcmp(line1, line2) != 0)
            break;
        if (++nlines >= MAXLINES) {
            fprintf(stderr, "%s: too many lines to read\n", prog);
            exit(1);
        }
    }

    if (!strcmp(line1, line2))  /* lines are equal if strcmp returns 0 */
        printf("%s and %s are the same.\n", argv[1], argv[2]);
    else {
        printf("They first differ on line %d:\n", nlines);
        printf("%s: %s", argv[1], c1 == NULL ? "\n" : line1);
        printf("%s: %s", argv[2], c2 == NULL ? "\n" : line2);
    }
    fclose(fp1);
    fclose(fp2);
    exit(0);
}
