# Solve the problem from the second set here

# 2nd problem -> second set problem 8

def get_nth_fibo(n):
    """
    returns [n]th fibonacci number
    :param n: natural number
    :return: natural number representing [n]th fibonacci number
    """

    if n <= 1:
        return 1

    a = 1
    b = 1

    for i in range(2, n + 1):
        c = a + b
        a = b
        b = c

    return c

def find_smallest_fibo(n):
    """
    returns smallest fibonacci number larger than given [n]
    :param n: natural number
    :return: natural number, representing smallest fibonacci number larger than given [n]
    """

    i = 0

    while get_nth_fibo(i) <= n:
        i += 1

    return get_nth_fibo(i)


if __name__ == "__main__":
    n = int(input("Please enter a natural number: "))
    print("Smallest fibonacci number larger than " + str(n) + " is " + str(find_smallest_fibo(n)))