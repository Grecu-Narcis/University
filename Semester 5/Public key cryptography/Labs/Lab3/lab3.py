import random


def decompose_n(n: int):
    s, t = 0, n - 1

    while t % 2 == 0:
        s += 1
        t //= 2

    return s, t


def compute_sequence(a: int, n: int, s: int, t: int):
    prev = None

    for i in range(s + 1):
        exponent = pow(2, i) * t
        result = pow(a, exponent, n)

        if i == 0 and result == 1:
            return True

        if result == 1 and prev == n - 1:
            return True

        prev = result

    return False


def is_prime(n: int, k: int = 4):
    s, t = decompose_n(n)

    for i in range(k):
        a = random.randint(2, n - 1)

        if not compute_sequence(a, n, s, t):
            print(f"Test with a = {a} failed!")
            return False

        print(f"Test with a = {a} passed!")

    return True


if __name__ == "__main__":
    n = int(input("n = "))
    k = 4

    if is_prime(n, k):
        print(f"{n} is probably prime!\nProbability is {1 - 1/pow(4, k)}")

    else:
        print(f"{n} is composite!")
