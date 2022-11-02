"""
The sequence a = a1, ..., an with distinct
integer numbers is given. Determine all subsets
of elements having the sum divisible by a given n.
"""


def sum(sequence, subset):
    """
    Function to compute the sum of the elements in the subset
    :param sequence: list of integer
    :param subset: list of integer, where subset[i] = 1 if sequence[i] belongs to subset, 0 otherwise
    :return: sum of elements in subset
    """
    result = 0

    for i in range(len(subset)):
        if subset[i] == 1:
            result += sequence[i]

    return result


def is_solution(sequence, subset):
    """
    Function to check if a subset is solution
    :param sequence: list of integer
    :param subset: list of integer, where subset[i] = 1 if sequence[i] belongs to subset, 0 otherwise
    :return: True if the subset is solution, False otherwise
    """

    if len(subset) != len(sequence):
        return False

    if sum(sequence, subset) % len(sequence) == 0:
        return True

    return False


def is_consistent(sequence, subset):
    """
    Function to check if a partial solution is consistent
    :param sequence: list of integer
    :param subset: list of integer, where subset[i] = 1 if sequence[i] belongs to subset, 0 otherwise
    :return: True if solution is consistent, False otherwise
    """
    if len(subset) <= len(sequence):
        return True

    return False


def print_solution(sequence, subset):
    """
    Function to print solution
    :param sequence: list of integer
    :param subset: list of integer, where subset[i] = 1 if sequence[i] belongs to subset, 0 otherwise
    :return: None
    """
    solution = []

    for i in range(len(subset)):
        if subset[i] == 1:
            solution.append(sequence[i])

    print(solution)


def find_solutions(sequence, subset):
    """
    Function to recursively find all solutions
    :param sequence: list of integer, representing all the numbers available
    :param subset: list of integer, representing the current subset
    :return: None
    """
    if is_solution(sequence, subset):
        print_solution(sequence, subset)

    else:
        for item in [0, 1]:
            if is_consistent(sequence, subset + [item]):
                find_solutions(sequence, subset + [item])


def initial_value():
    return -1


def next_elem(x):
    if x[len(x) - 1] == 1:
        return None

    return x[len(x) - 1] + 1


def iterative_backtracking(sequence):
    x = [initial_value()]

    while len(x) > 0:
        el = next_elem(x)
        while el is not None:
            x[-1] = el
            if is_consistent(sequence, x):
                if is_solution(sequence, x):
                    print_solution(sequence, x)
                else:
                    x.append(-1)
                    break

            el = next_elem(x)

        if el is None:
            x = x[:-1]


if __name__ == "__main__":
    number_of_elements = int(input("Enter the number of elements in the sequence: "))

    numbers = [int(x) for x in input().split()[:number_of_elements]]
    find_solutions(numbers, [])

    print("--------------------------")

    iterative_backtracking(numbers)
