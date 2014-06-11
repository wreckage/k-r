/* K&R - Exercise 1-24. Write a program to check a C program for 
 * rudimentary syntax errors like unmatched parentheses, 
 * brackets and braces. Don't forget about quotes, both 
 * single and double, escape sequences, and comments. (This 
 * program is hard if you do it in full generality.)  */
#include <stdio.h>

char check_char(char c);
void check_err(void);

int err, paran, quote, dbl_quote;

void check_it(int c) {
    if (c == '(')
        paran++;
    if (c == ')')
        paran--;
    if (c == '"')
        dbl_quote++;
    if (c == '\'')
        quote++;
}

void check_err(void) {
    if (paran > 0) {
        err++;
        printf("You forgot to close %d parathesis!\n", paran);
    }
    if (paran < 0) {
        err++;
        printf("You left %d parathesis open!\n", -paran);
    }
    if ((dbl_quote % 2) > 0) {
        err++;
        printf("Warning: Unmatched double quote!\n");
    }
    if ((quote % 2) > 0) {
        err++;
        printf("Warning: Unmatched single quote!\n");
    }
    if (err == 0)
        printf("All clear!\n");
}

int main(void) {

    int c;
    paran = quote = dbl_quote = 0;

    while ((c = getchar()) != EOF)
        check_it(c);

    check_err();
    return 0;
}
