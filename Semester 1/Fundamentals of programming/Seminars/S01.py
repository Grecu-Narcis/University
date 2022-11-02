import math

#1.a) sum of first n natural numbers

def sum_of_first_natural_numbers(n):
    """ Computes the sum of the first n natural numbers.

    Given a natural number n, we will calculate the sum of the first n natural numbers.
    :param n: natural number
    :return: returns the sum of the first [n] natural numbers
    """
    sum = 0

    for i in range(n):
        sum = sum + i
    
    return sum

#1.c) gcd of two given integers

def gcd(a, b):
    while b != 0:
        a, b = b, a % b

    return a if a > 0 else -a

#1.b) check if a given number is prime

def check_primality(n):
    if n == 2:
        return True

    if n < 2 or n % 2 == 0:
        return False

    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False

    return True  

#1.d) compute the next prime number bigger than given integer n
def next_prime(n):
    n = n + 1

    while check_primality(n) == False:
        n = n + 1

    return n

#1.e) print the next k primes bigger than given integer n
def next_k_primes(n, k):
    for i in range(k):
        n = next_prime(n)
        print(n)


if __name__ == '__main__':
    next_k_primes(6, 3)
