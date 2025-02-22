import random
import time
from prettytable import PrettyTable


def gcd_euclidean_subtraction(a, b):
    # Continue looping until both numbers are equal
    while a != b:
        # If a is greater than b, subtract b from a
        if a > b:
            a = a - b
        # If b is greater than a, subtract a from b
        else:
            b = b - a

    # When a and b are equal, we have found the GCD
    return a


def gcd_bruteforce(a, b):
    # we look from the biggest value and check if the current number divides both
    for i in range(min(a, b), 0, -1):
        # if current number divides both we found the gcd
        if a % i == 0 and b % i == 0:
            return i

    return 1


def gcd_stein(a, b):
    # gcd(x, x) = x
    if a == b:
        return a

    # gcd(x, 0) = x, for any x
    if a == 0:
        return b
    if b == 0:
        return a

    # Both a and b are even
    # gcd(2u, 2v) = 2 * gcd(u, v)
    if (a & 1) == 0 and (b & 1) == 0:
        return gcd_stein(a >> 1, b >> 1) << 1

    # a is even, b is odd
    # gcd(u, 2v) = gcd(u, v)
    elif (a & 1) == 0:
        return gcd_stein(a >> 1, b)
    # a is odd, b is even
    elif (b & 1) == 0:
        return gcd_stein(a, b >> 1)

    # Both are odd
    # gcd(u, v) = gcd(min(u,v), max(u,v) - min(u,v))
    elif a > b:
        return gcd_stein(a - b, b)
    else:
        return gcd_stein(a, b - a)


# Generate a set of random natural numbers
random_pairs = [(random.randint(1, 10 ** 6), random.randint(1, 10 ** 6)) for _ in range(5)]
random_pairs.append((random.randint(10 ** 8, 10 ** 9), random.randint(10 ** 8, 10 ** 9)))


# Function to measure execution time of an algorithm
def measure_time(func, a, b):
    start_time = time.perf_counter()
    result = func(a, b)
    end_time = time.perf_counter()
    return end_time - start_time, result


def main():
    # Collecting results
    results = {
        "Euclidean": [],
        "Bruteforce": [],
        "Stein": []
    }

    for a, b in random_pairs:
        euclidean_time, euclidean_result = measure_time(gcd_euclidean_subtraction, a, b)
        bruteforce_time, bruteforce_result = measure_time(gcd_bruteforce, a, b)
        stein_time, stein_result = measure_time(gcd_stein, a, b)

        results["Euclidean"].append((euclidean_time, euclidean_result))
        results["Bruteforce"].append((bruteforce_time, bruteforce_result))
        results["Stein"].append((stein_time, stein_result))

    print(results)


if __name__ == "__main__":
    main()
