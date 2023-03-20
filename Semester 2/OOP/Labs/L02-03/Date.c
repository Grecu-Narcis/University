#include "Date.h"

#include <time.h>

Date createDate(int day, int month, int year)
{
    Date createdDate;
    
    createdDate.day = day;
    createdDate.month = month;
    createdDate.year = year;
    
    return createdDate;
}


Date getCurrentDate()
{
    time_t currentTime = time(NULL);
    struct tm localTime = *(localtime)(&currentTime);

    Date currentDate = createDate(localTime.tm_mday, localTime.tm_mon + 1, localTime.tm_year + 1900);

    return currentDate;
}


int isLeapYear(int yearToCheck)
{
    if (yearToCheck % 400 == 0)
        return 1;

    if (yearToCheck % 100 == 0)
        return 0;

    if (yearToCheck % 4 == 0)
        return 1;

    return 0;
}


int getNumberOfDaysSinceFirstYear(Date dateToCompute)
{
    int numberOfPassedDays = 0;

    for (int year = 1; year < dateToCompute.year; year++)
        if (isLeapYear(year))
            numberOfPassedDays += 366;
        else
            numberOfPassedDays += 365;

    int numberOfDaysForMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int month = 1; month < dateToCompute.month; month++)
        if (month == 2)
        {
            if (isLeapYear(dateToCompute.year))
                numberOfPassedDays += 29;

            else
                numberOfPassedDays += 28;
        }

        else
            numberOfPassedDays += numberOfDaysForMonth[month];

    numberOfPassedDays += dateToCompute.day;

    return numberOfPassedDays;
}


int getNumberOfDaysUntilCurrentDay(Date dateToCompute)
{
    Date currentDate = getCurrentDate();


    return getNumberOfDaysSinceFirstYear(dateToCompute) - getNumberOfDaysSinceFirstYear(currentDate);
}
