/* K&R - Exercise 5-8. There is no error checking in day_or_year or
 * month_day. Remedy this defect. */

#include <stdio.h>

int day_of_year(int y, int m, int d);
int month_day(int y, int yd, int *, int *);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (month < 1 || month > 12) {
        printf("ERROR: INVALID MONTH GIVEN.\n");
        return -1;
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (day > daytab[leap][month] || day < 1) {
        printf("ERROR: INVALID DAY GIVEN.\n");
        return -1;
    }

    for (i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    if (yearday > 365 || yearday < 1) {
        printf("ERROR: INVALID DAY OF YEAR\n");
        return -1;
    }

    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
    return 0;
}

int main(void)
{
    int year, month, day, yearday;
    int status;

    /* Valid arguments */
    printf("Trying valid arguments...\n");
    year = 2014;
    month = 5;
    day = 25;
    printf("Day of year for %d %d %d: ", year, month, day);
    yearday = day_of_year(year, month, day);
    printf("%d\n", yearday);

    month_day(year, yearday, &month, &day);
    printf("Month, day from year %d and day of year %d: ", year, yearday);
    printf("%d %d\n", month, day);

    /* Invalid arguments */
    printf("Trying invalid arguments...\n");
    year = 2014;
    month = 5;
    day = 32;
    yearday = day_of_year(year, month, day);

    year = 2014;
    yearday = 366;
    status = month_day(year, yearday, &month, &day);
}
