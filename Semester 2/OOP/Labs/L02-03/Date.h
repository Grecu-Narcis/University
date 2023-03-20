#pragma once

typedef struct
{
	int day, month, year;
} Date;

Date createDate(int day, int month, int year);
int getNumberOfDaysUntilCurrentDay(Date dateToCompute);
