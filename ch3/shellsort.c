/* Shell sort example.
 * This is not an exercise, but I like it so I decided to include it anyway. 
 * */

#include <stdio.h>

#define MAX 10

void shellsort(int v[], int n);

/* shellsort: sort v[0] ... v[n-1] into increasing order */
void shellsort(int v[], int n)
{
    int i, j, gap, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j-=gap) {
                temp = v[j+gap];
                v[j+gap] = v[j];
                v[j] = temp;
            }
}

int main(void)
{
    int a[MAX] = { 1, 5, 2, 8, 9, 3, 7, 6, 4, 0 };
    int i;

    printf("Before shellsort:\n");
    for (i = 0; i < MAX; i++)
        printf("%d ", a[i]);
    printf("\n");

    shellsort(a, MAX);

    printf("After shellsort:\n");
    for (i = 0; i < MAX; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
