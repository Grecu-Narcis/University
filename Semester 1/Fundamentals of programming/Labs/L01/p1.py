# Solve the problem from the first set here

# 1st problem -> first set problem 4
def get_digits(n):
    """
    takes a natural number and returns its digits in descending order
    :param n: natural number
    :return: list containing digits of [n] in descending order, ex: n = 233 return [3, 3, 2]
    """

    if n == 0:
        return [0]

    digits = []

    while n != 0:
        digits.append(n % 10)
        n = n // 10

    digits.sort(reverse=True)
    return digits


def find_largest_number(n):
    """
    Finds the largest number that can be written with the same digits as [n]
    :param n: natural number
    :return: natural number, representing the biggest number that can be written
    """
    digits = get_digits(n)
    result = 0

    for digit in digits:
        result = result * 10 + digit

    return result


if __name__ == '__main__':
    n = int(input("Enter a natural number: "))
    print("Largest number that can be written with the same digits as " + str(n) + " is " + str(find_largest_number(n)))
