/* Exercise 3-1. Our binary search makes two tests 
 * inside the loop, when one would suffice (at 
 * the price of more tests outside.) Write a version 
 * with only one test inside the loop and 
 * measure the difference in run-time.  */

/* NOTE: This solution makes use of Paul Griffiths test driver,
 * which can be found in his solution here:
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_3:Exercise_1  */

#include <stdio.h>
#include <time.h>

#define MAX_ELEMENT 20000

int binsearch(int x, int v[], int n);
int mybinsearch(int x, int v[], int n);

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else /* found match */
            return mid;
    }
    return -1; /* no match */
}

int mybinsearch(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    mid = (low+high)/2;
    while (low < high && x != v[mid]) {
        if (x < v[mid])
            high = mid;
        else
            low = mid;
        mid = (low+high)/2;
    }
    return (x == v[mid]) ? mid : -1;
}




/*  Outputs approximation of processor time required
    for our two binary search functions. We search for
    the element -1, to time the functions' worst case
    performance (i.e. element not found in test data)   */

int main(void) {
    int testdata[MAX_ELEMENT];
    int index;                  /*  Index of found element in test data  */
    int n = -1;                 /*  Element to search for  */
    int i;
    clock_t time_taken;

    /*  Initialize test data  */
    
    for ( i = 0; i < MAX_ELEMENT; ++i )
        testdata[i] = i;
    
    
    /*  Output approximation of time taken for
        100,000 iterations of binsearch()       */
    
    for ( i = 0, time_taken = clock(); i < 100000; ++i ) {
        index = binsearch(n, testdata, MAX_ELEMENT);
    }
    time_taken = clock() - time_taken;
    
    if ( index < 0 )
        printf("Element %d not found.\n", n);
    else
        printf("Element %d found at index %d.\n", n, index);
    
    printf("binsearch() took %lu clocks (%lu seconds)\n",
           (unsigned long) time_taken,
           (unsigned long) time_taken / CLOCKS_PER_SEC);
    
    
    /*  Output approximation of time taken for
        100,000 iterations of mybinsearch()        */
    
    for ( i = 0, time_taken = clock(); i < 100000; ++i ) {
        index = mybinsearch(n, testdata, MAX_ELEMENT);
    }
    time_taken = clock() - time_taken;
    
    if ( index < 0 )
        printf("Element %d not found.\n", n);
    else
        printf("Element %d found at index %d.\n", n, index);
    
    printf("mybinsearch() took %lu clocks (%lu seconds)\n",
           (unsigned long) time_taken,
           (unsigned long) time_taken / CLOCKS_PER_SEC);
    
    return 0;
}
