/* K&R - Exercise 8-1. Rewrite the program cat from Chapter 7 
 * using read, write, open, and close instead of their standard 
 * library equivalents. Perform experiments to determine the relative 
 * speeds of the two versions.  */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define IN 0
#define OUT 1
#define ERR 2

/* cat: concatenate files, low-level I/O version */
int main(int argc, char *argv[])
{
    int fd;
    void filecopy(int, int);

    if (argc == 1)  /* no args; copy standard input */
        filecopy(IN, OUT);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "cat: can't open %s\n", *argv);
                return 1;
            } else {
                filecopy(fd, OUT);
                close(fd);
            }
    return 0;
}

/* filecopy: copy file with file descriptor fdin to 
 * file with file descriptor fdout */
void filecopy(int fdin, int fdout)
{
    int n;
    char buf[BUFSIZ];

    while ((n = read(fdin, buf, BUFSIZ)) > 0)
        if (write(fdout, buf, n) != n) {
            fprintf(stderr, "write error\n");
            exit(1);
        }
}
