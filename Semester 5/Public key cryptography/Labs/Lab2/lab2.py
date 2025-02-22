def compute_order(k, n):
    result = 0
    for i in range(1, n + 1):
        result += k
        if result % n == 0:
            return i

    return n


def main():
    n = int(input("n = "))

    for i in range(0, n):
        if compute_order(i, n) == n:
            print(str(i) + " is a generator")

# g is a generator if ord(g) = ord(GROUP)

if __name__ == "__main__":
    main()