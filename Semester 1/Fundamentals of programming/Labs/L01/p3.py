# Solve the problem from the third set here

# 3rd problem -> third set problem 12

def is_leap_year(year):
    """
    function to check if a given year is leap
    :param year: natural number >= 1
    :return: boolean
    True if [year] is leap, False otherwise
    """

    if year % 400 == 0:
        return True

    if year % 4 == 0 and year % 100 != 0:
        return True

    return False


def get_years_passed(year):
    """
    compute the number of whole years that passed since 1st year (anno domini)
    and returns the sum of days of each year passed
    :param year: natural number
    :return: natural number representing the sum of days of each year passed
    """

    result = 0

    # for each whole year that passed we add the corresponding number of days
    for i in range(1, year):
        if is_leap_year(i):
            result += 366

        else:
            result += 365

    return result


def get_moths_passed(year, month):
    """
    return the number of days of months that passed completely in [year]
    :param year: natural number
    :param month: natural number
    :return: natural number representing sum of days of months completely passed in [year]
    """

    result = 0
    month_day = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    # for each whole month that passed in the current [year] we add the corresponding number of days
    for i in range(1, month):
        if i == 2:
            if is_leap_year(year):
                result += 29
            else:
                result += 28
        else:
            result += month_day[i]

    return result


def get_days_count(year, month, day):
    """
    compute the number of days passed since 01.01.0001 (ANNO DOMINI, Jan 1st) up to [day].[month].[year]
    :param year: natural number >= 1
    :param month: natural number in [1, 12]
    :param day: natural number in [1, 31] (at most)
    :return: natural number representing the number of days passed
    """

    return get_years_passed(year) + get_moths_passed(year, month) + day


if __name__ == '__main__':
    b_year = int(input("Enter year of birth: "))
    b_month = int(input("Enter month of birth: "))
    b_day = int(input("Enter day of birth: "))

    c_year = int(input("Enter current year: "))
    c_month = int(input("Enter current month: "))
    c_day = int(input("Enter current day: "))

    days_passed = get_days_count(c_year, c_month, c_day) - get_days_count(b_year, b_month, b_day) + 1

    print("The number of days that passed is: ", days_passed)