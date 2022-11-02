# Seminar 2
# find a number in a list

def check_for_number(l, v):
    if len(l) == 0:
        return False

    if v == l[0]:
        return True

    return check_for_number(l[1:], v)


def binary_search(l, v):
    if len(l) == 0:
        return False

    mid = (len(l) - 1) // 2

    if v == l[mid]:
        return True

    if v < l[mid]:
        return binary_search(l[0: mid], v)

    return binary_search(l[mid + 1:], v)


def merge(left, right):
    i, j = 0, 0

    result = []

    while len(left) and len(right):
        if left[0] < right[0]:
            result.append(left.pop(0))

        else:
            result.append(right.pop(0))

    result.extend(left + right)

    return result


def merge_sort(l):
    if len(l) < 2:
        return l

    mid = len(l) // 2

    left = merge_sort(l[:mid])
    right = merge_sort(l[mid:])

    return merge(left, right)


def print_options():
    pass


def run_menu():
    commands = {1:check_for_number, 2:binary_search}

    while True:
        print_options()

        op = input("Option is: ")

        if op == 'x':
            break

        op = int(op)

        commands[op]()


if __name__ == "__main__":
    print(merge_sort([2,1,6,1,3,5]))
