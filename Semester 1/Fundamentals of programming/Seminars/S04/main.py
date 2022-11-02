def binary_search(numbers, start, end, item):
    left = start
    right = end

    while left <= right:
        mid = (left + right) // 2

        if numbers[mid] == item:
            return mid

        if numbers[mid] < item:
            left = mid + 1

        else:
            right = mid - 1

    return -1


def exponential_search(numbers, item):
    index = 1

    while index < len(numbers) and item > numbers[index]:
        index = index * 2

    result = 0
    if index >= len(numbers):
        result = binary_search(numbers, index//2, len(numbers) - 1, item)

    else:
        result = binary_search(numbers, index//2, index, item)

    return result != -1


def x_to_the_n(x, n):
    if n == 0:
        return 1

    result = x_to_the_n(x, n // 2)

    if n % 2 == 1:
        return x * result * result

    return result * result


def find_max_of_list(numbers, left, right):
    if left >= right:
        return numbers[left]

    mid = (left + right) // 2

    max1 = find_max_of_list(numbers, left, mid)
    max2 = find_max_of_list(numbers, mid + 1, right)

    if max1 > max2:
        return max1

    return max2


def gcd(a, b):
    if a == 0:
        return b

    if b == 0:
        return a

    return gcd(b, a % b)


def gcd_of_list(numbers):
    if len(numbers) == 0:
        return 1

    if len(numbers) == 1:
        return numbers[0]

    mid = len(numbers) // 2

    gcd1 = gcd_of_list(numbers[:mid])
    gcd2 = gcd_of_list(numbers[mid:])

    return gcd(gcd1, gcd2)


def back(x, n):
    pass


if __name__ == "__main__":
    numbers = [int(x) for x in input().split()]

    print(gcd_of_list(numbers))
