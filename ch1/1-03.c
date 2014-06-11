/*  Exercise 1-3. Modify the temperature conversion 
 *  program to print a heading above the table.  */

#include <stdio.h>

main() {
    float fahr, celsius;
    float upper, lower, step;

    upper = 300;
    lower = 0;
    step = 20;

    fahr = lower;

    printf("Fahrenheit to Celsius Table\n");
    printf("------------------------------\n");
    printf("%s %s\n", "Fahrenheit", "Celsius");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%10.0f %7.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
