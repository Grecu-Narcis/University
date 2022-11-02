import random


def display_menu():
    """
    Shows the available options to the user
    :return: natural number in interval [0, 4] representing the option chosen by the user
    """

    print("Press: ")
    print("1 to generate a list of n random numbers")
    print("2 to sort numbers using first sorting algorithm ie selection sort")
    print("3 to sort numbers using second sorting algorithm ie stooge sort")
    print("4 to show list")
    print("0 to exit")

    option = int(input("Choose your option: "))

    return option


def main_menu():
    """
    Handles the option chosen by the user
    """

    numbers = []

    while True:
        option = display_menu()

        if option == 1:
            list_size = int(input("Enter number of elements in list: "))
            numbers = generate_numbers(list_size)

        elif option == 2:
            step = int(input("Enter the step for displaying partially sorted list: "))
            sort1(numbers, step)

        elif option == 3:
            step = int(input("Enter the step for displaying partially sorted list: "))
            sort2(numbers, step)

        elif option == 4:
            print("The list is: ", numbers)

        elif option == 0:
            break


def menu_option_1():
    """
    Menu for option 1. Requests from user a natural number representing the size of list
    :return:list of n random natural numbers from interval [0, 100]
    """
    n = int(input("Please enter number of elements in list: "))
    numbers = generate_numbers(n)

    return numbers


def generate_numbers(n):
    numbers = []

    for i in range(n):
        numbers.append(random.randint(0, 100))

    return numbers


def sort1(numbers, step):
    """
    Sorts the list [numbers] using selection sort and prints the list at every [step] swaps
    :param numbers: list of natural numbers
    :param step: natural number
    """
    swaps = 0

    for i in range(len(numbers)):
        min_index = i

        for j in range(i, len(numbers)):
            if numbers[j] < numbers[min_index]:
                min_index = j

        numbers[i], numbers[min_index] = numbers[min_index], numbers[i]
        swaps += 1

        if swaps == step:
            print(numbers)
            swaps = 0


def sort2(numbers, step):
    """
    Sorts the list [numbers] using stooge sort
    :param numbers: list of natural number
    :param step: natural number
    """
    stooge_sort(numbers, step, 0, len(numbers) - 1, 0)


def stooge_sort(numbers, step, left, right, swaps):
    """
    Sorts the sublist numbers[left:right+1] using stooge_sort and
    displays the partially sorted list at every [step] swaps
    :param numbers: list of natural number
    :param step: natural number
    :param left: natural number in interval [0, len([numbers])-1]
    :param right: natural number in interval [0, len([numbers])-1]
    :param swaps: natural number
    """
    if numbers[left] > numbers[right]:
        numbers[left], numbers[right] = numbers[right], numbers[left]
        swaps += 1

        if swaps == step:
            print(numbers)
            swaps = 0

    if right - left + 1 > 2:  # if we have at least 3 elements in subarray
        cut_point = (right - left + 1) // 3

        stooge_sort(numbers, step, left, right - cut_point, swaps)
        stooge_sort(numbers, step, left + cut_point, right, swaps)
        stooge_sort(numbers, step, left, right - cut_point, swaps)


if __name__ == '__main__':
    main_menu()
