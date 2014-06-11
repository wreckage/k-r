/* K&R - Exercise 2-1. Write a program to determine the 
 * ranges of char, short, int, and long variables, both 
 * signed and unsigned, by printing appropriate values 
 * from standard headers and by direct computation. Harder 
 * if you compute them: determine the ranges of the various 
 * floating-point types.  */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    printf("The number of bits in a bite: %d\n", CHAR_BIT);
    printf("Minimum value for a signed char: %d\n", SCHAR_MIN);
    printf("Maximum value for a signed char: %d\n", SCHAR_MAX);
    printf("Maximum value for an usigned char: %d\n", UCHAR_MAX);
    printf("Minimum value for a short int: %d\n", SHRT_MIN);
    printf("Maximum value for a short int: %d\n", SHRT_MAX);
    printf("Maximum value for an unsigned short int: %d\n", USHRT_MAX);
    printf("Minimum value for an int: %d\n", INT_MIN);
    printf("Maximum value for an int: %d\n", INT_MAX);
    printf("Maximum value for an unsigned int: %u\n", UINT_MAX);
    printf("Minimum value for long int: %ld\n", LONG_MIN);
    printf("Maximum value for long int: %ld\n", LONG_MAX);
    printf("Maximum value for an unsigned long int: %lu\n", ULONG_MAX);
    printf("\nNow floating points...\n");
    printf("Minimum floating point value: %f\n", FLT_MIN);
    printf("Maximum floating point value: %f\n", FLT_MAX);
    printf("Minimum double floating point value: %f\n", DBL_MIN);
    printf("Maximum double floating point value: %f\n", DBL_MAX);
    return 0;
}
