#
# Write the implementation for A5 in this file
#

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def is_digit(ch):
    if '0' <= ch <= '9':
        return True

    return False


def convert_char_to_digit(ch):
    return ord(ch) - ord('0')


def create_complex(number='0'):
    number = number.replace(" ", "")

    if 'i' not in number:
        return [int(number), 0]

    result = []
    index, component, sign = 0, 0, 1

    if number[index] == '-':
        if number[index + 1] == 'i':
            return [0, -1]

        sign = -1
        index += 1

    while index < len(number) and is_digit(number[index]):
        component = component * 10 + convert_char_to_digit(number[index])
        index += 1

    component = sign * component

    if number[index] == 'i':
        return [0, component]

    result.append(component)

    if number[index] == '+':
        sign = 1

    else:
        sign = -1

    index += 1

    if number[index] == 'i':
        result.append(sign)
        return result

    component = 0

    while index < len(number) and is_digit(number[index]):
        component = component * 10 + convert_char_to_digit(number[index])
        index += 1

    component = sign * component

    result.append(component)

    return result


def get_real_part(number):
    return number[0]


def set_real_part(number, value):
    number[0] = value


def get_imaginary_part(number):
    return number[1]


def set_imaginary_part(number, value):
    number[1] = value


def to_str(number):
    if number[0] == 0 and number[1] == 0:
        return '0'

    if number[0] == 0:
        if number[1] == 1:
            return 'i'

        if number[1] == -1:
            return '-i'

        return str(number[1]) + 'i'

    if number[1] == 0:
        return str(number[0])

    if number[1] == 1:
        return str(number[0]) + '+i'

    if number[1] == -1:
        return str(number[0]) + '-i'

    if number[1] > 0:
        return str(number[0]) + '+' + str(number[1]) + 'i'

    return str(number[0]) + str(number[1]) + 'i'

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def create_complex(number):
    number = number.replace(" ", "")
    result = {
        "real": 0,
        "imaginary": 0
    }

    if 'i' not in number:
        result["real"] = int(number)
        return result

    index, component, sign = 0, 0, 1

    if number[index] == '-':
        if number[index + 1] == 'i':
            result['imaginary'] = -1
            return result

        sign = -1
        index += 1

    while index < len(number) and is_digit(number[index]):
        component = component * 10 + convert_char_to_digit(number[index])
        index += 1

    component = sign * component

    if number[index] == 'i':
        result["imaginary"] = component
        return result

    result["real"] = component

    if number[index] == '+':
        sign = 1

    else:
        sign = -1

    index += 1
    component = 0

    if number[index] == 'i':
        result['imaginary'] = sign
        return result

    while index < len(number) and is_digit(number[index]):
        component = component * 10 + convert_char_to_digit(number[index])
        index += 1

    component = sign * component

    result["imaginary"] = component

    return result


def get_real_part(complex_number):
    return complex_number["real"]


def get_imaginary_part(complex_number):
    return complex_number["imaginary"]


def set_real_part(complex_number, value):
    complex_number["real"] = value


def set_imaginary_part(complex_number, value):
    complex_number["imaginary"] = value


def to_str(number):
    if number['real'] == 0 and number['imaginary'] == 0:
        return '0'

    if number['real'] == 0:
        if number['imaginary'] == 1:
            return 'i'

        if number['imaginary'] == -1:
            return '-i'

        return str(number['imaginary']) + 'i'

    if number['imaginary'] == 0:
        return str(number['real'])

    if number['imaginary'] == 1:
        return str(number['real']) + '+i'

    if number['imaginary'] == -1:
        return str(number['real']) + '-i'

    if number['imaginary'] > 0:
        return str(number['real']) + '+' + str(number['imaginary']) + 'i'

    return str(number['real']) + str(number['imaginary']) + 'i'


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def modulus(complex_number):
    return get_real_part(complex_number) ** 2 + get_imaginary_part(complex_number) ** 2


def property_1(numbers):
    """
    return length and elements of the longest subarray of numbers having the same modulus.
    :param numbers: list, representing the complex numbers
    :return: tuple, first element is
    """
    max_length, length, end = 0, 0, 0
    last_modulus = -1

    for i in range(len(numbers)):
        if modulus(numbers[i]) == last_modulus:
            length += 1

        else:
            if length > max_length:
                max_length = length
                end = i

            length = 1
            last_modulus = modulus(numbers[i])

    if length > max_length:
        max_length = length
        end = len(numbers)

    return max_length, numbers[end - max_length:end]


def property_2(numbers):
    """
    return the length and elements of the longest increasing subsequence, when considering each number's real part
    :param numbers: list, representing the complex numbers
    :return: tuple, first element is the length and the second one is a list representing
    the longest increasing subsequence
    """

    if len(numbers) == 0:
        return None

    length = [0 for i in range(len(numbers))]

    length[0] = 1

    for i in range(1, len(numbers)):
        for j in range(i):
            if get_real_part(numbers[j]) <= get_real_part(numbers[i]) and length[j] >= length[i]:
                length[i] = length[j] + 1

    index = 0

    for i in range(len(numbers)):
        if length[i] >= length[index]:
            index = i

    max_length = length[index]

    current_length = max_length

    elements = []

    while current_length != 0:
        if length[index] == current_length:
            elements.append(numbers[index])
            current_length -= 1

        index -= 1

    return max_length, elements[::-1]


#
# Write below this comment
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_options():
    print("Press 1 to read a list of complex numbers.")
    print("Press 2 to display the list.")
    print("Press 3 for properties.")
    print("Press 4 to exit.")


def option_1():
    result = []

    number_of_elements = int(input("Please enter the number of elements in the list: "))

    print("Please enter each complex number on a new line:")

    for i in range(number_of_elements):
        number = input()
        result.append(create_complex(number))

    return result


def print_list(numbers):
    for item in numbers:
        print(to_str(item))


def print_property_1(numbers):
    print("Length and elements of a longest subarray of numbers having the same modulus:")

    result = property_1(numbers)

    print("The length of subarray is: ", result[0])

    print("Elements in the subarray are: ")

    for i in range(len(result[1])):
        print(to_str(result[1][i]))


def print_property_2(numbers):
    print("The length and elements of a longest increasing subsequence, when considering each number's real part")

    result = property_2(numbers)

    print("The length of subsequence is: ", result[0])

    print("Elements in the subsequence are: ")

    for i in range(len(result[1])):
        print(to_str(result[1][i]))


def main_menu(numbers):
    while True:
        print_options()

        op = int(input("Your choice: "))

        if op == 1:
            numbers = option_1()

        if op == 2:
            print_list(numbers)

        if op == 3:
            print_property_1(numbers)
            print_property_2(numbers)

        if op == 4:
            break


if __name__ == "__main__":
    numbers = [[2, 3], [5, 3], [1, 0], [0, 1], [7, 2], [6, 4], [1, -1], [3, -5], [0, 0], [-5, -5]]
    numbers = [{'real': 2, 'imaginary': 3}, {'real': 5, 'imaginary': 3}, {'real': 1, 'imaginary': 0}, {'real': 0, 'imaginary': 3},
               {'real': 2, 'imaginary': 3}, {'real': 2, 'imaginary': 3}, {'real': 2, 'imaginary': 3}, {'real': 2, 'imaginary': 3},
               {'real': 2, 'imaginary': 3}, {'real': 2, 'imaginary': 3}]
    main_menu(numbers)
