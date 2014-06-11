/* K&R - Exercise 1.15 */

#include <stdio.h>

#define START 0
#define STEP 20
#define COUNT 15

int f2c(int f);

main() {
    int fahr, celsius;
    int i;

    fahr = START;
    for (i = 0; i < COUNT; i++) {
        celsius = f2c(fahr);
        printf("%3d %6d\n", fahr, celsius);
        fahr = fahr + STEP;
    }
    return 0;
}

int f2c(int fahr) {
    int celsius;

    celsius = 5 * (fahr-32) / 9;
    return celsius;
}
