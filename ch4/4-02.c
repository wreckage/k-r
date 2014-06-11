/* K&R - Exercise 4-2 p.67
 * Extend atof to handle scientific notation
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 100

double atof(char s[]);
int getline(char line[], int limit);

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;

    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power, n;
    int i, sign, esign, val2;

    n = 10.0;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    /* support for scientific notation */
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    if (s[i] == '-') {
        i++;
        n = .1;
    }
    else if (s[i] == '+')
        i++;
    
    for (val2 = 0; isdigit(s[i]); i++)
        val2 = 10 * val2 + (s[i] - '0');

    return (sign * val / power) * pow(n, val2);
}

/* atoi: convert string s to integer using atof */
int atoi(char s[])
{
    double atof(char s[]);

    /* the cast states explicitly that we want to return the double
     * as an int. */
    return (int) atof(s);
}
/* rudimentary calculator */
/* note that atof and getline are declared explicity with the
 * main function to indicate that they do not return int values
main(void)
{
    double sum, atof(char []);
    char line[MAXLINE];
    int getline(char line[], int max);
    sum = 0;
    while (getline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));
    return 0;
}
*/

main(void)
{
    char s[] = "56.22e11";
    double n;

    printf("%s\n", s);
    n = atof(s);
    printf("%.12f\n", n);

    return 0;
}
