def is_prime(n):
    if n == 2:
        return True

    elif n < 2 or n % 2 == 0:
        return False

    for i in range(3, n, 2):
        if n % i == 0:
            return False

    return True


def number_of_divisors(n):
    result = 0

    for i in range(2, n):
        if is_prime(i) and n % i == 0:
            result += 1

    return result


def get_nth_divisor(term, n):
    result = 0

    for i in range(2, term):
        if is_prime(i) and term % i == 0:
            result += 1
            if result == n:
                return i


def get_nth_term(n):
    if n == 1:
        return 1

    term = 1
    n = n - 1

    while n != 0:
        term = term + 1
        if is_prime(term):
            n = n-1

        elif number_of_divisors(term) < n:
            n = n - number_of_divisors(term)

        else:
            return get_nth_divisor(term, n)

    return term


n = int(input("enter a number: "))
print(get_nth_term(n))