import math
import random

from sympy import randprime


def generate_n(start, end):
    p = randprime(start, end)
    q = randprime(start, end)

    while p == q:
        p = randprime(start, end)
        q = randprime(start, end)

    n = p * q
    phi_n = (p - 1) * (q - 1)

    return n, phi_n


def select_element(phi_n):
    while True:
        number = random.randint(2, phi_n - 1)

        if math.gcd(number, phi_n) == 1:
            return number


def generate_keys(start, end):
    n, phi_n = generate_n(start, end)
    e = select_element(phi_n)

    d = pow(e, -1, phi_n)

    return n, e, d

