/* Quicksort example.
 * This is not an exercise, but I like it so I decided to include it anyway. 
 * */

#include <stdio.h>

#define MAX 10

void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main(void)
{
    int a[MAX] = { 1, 5, 2, 8, 9, 3, 7, 6, 4, 0 };
    int i;

    printf("Before quicksort:\n");
    for (i = 0; i < MAX; i++)
        printf("%d ", a[i]);
    printf("\n");

    qsort(a, 0, MAX);

    printf("After quicksort:\n");
    for (i = 0; i < MAX; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
