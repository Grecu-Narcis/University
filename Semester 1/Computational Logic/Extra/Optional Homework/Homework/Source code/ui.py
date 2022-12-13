from functions import *


def menu():
    print("1. Add two numbers in a base")
    print("2. Subtract two numbers in a base")
    print("3. Multiply a number by a digit in a base")
    print("4. Divide a number by a digit in a base")
    print("5. Convert number from one base to another using 10 as intermediary base")
    print("6. Exit")


def main_menu():
    while True:
        menu()
        choice = int(input("Enter your choice: "))
        if choice == 1:
            base = int(input("Enter base: "))
            x = input("Enter first number: ")
            y = input("Enter second number: ")

            x = Number(x, base)
            y = Number(y, base)

            z = add_numbers(x, y, base)
            print("Result is: ", z)

        elif choice == 2:
            base = int(input("Enter base: "))
            x = input("Enter first number: ")
            y = input("Enter second number: ")

            x = Number(x, base)
            y = Number(y, base)

            z = sub_numbers(x, y, base)
            print("Result is: ", z)

        elif choice == 3:
            base = int(input("Enter base: "))
            x = input("Enter number: ")
            digit_to_multiply = convert_char_to_digit(input("Enter digit to multiply: "))
            x = Number(x, base)

            z = multiply_by_digit(x, digit_to_multiply, base)
            print("Result is: ", z)

        elif choice == 4:
            base = int(input("Enter base: "))
            x = input("Enter first number: ")
            digit_to_divide = convert_char_to_digit(input("Enter digit to divide: "))
            x = Number(x, base)

            z = divide_by_digit(x, digit_to_divide, base)
            print("Result is: ", z)

        elif choice == 5:
            base = int(input("Enter base: "))
            x = input("Enter number: ")
            base_to_convert = int(input("Enter base to convert: "))
            x = Number(x, base)

            z = convert_number(x, base_to_convert)
            print(f'{x} in base {base} is {z} in base {base_to_convert}')

        elif choice == 6:
            break

        else:
            print("Invalid choice")
