from Number import Number


def convert_char_to_digit(char):
    """
    Converts a character to a digit
    char: char
    :return: int
    """

    if char.isdigit():
        return int(char)
    else:
        return ord(char) - ord('A') + 10


def convert_digit_to_char(digit):
    """
    Converts a digit to a character
    digit: int
    :return: char
    """

    if digit < 10:
        return str(digit)
    else:
        return chr(ord('A') + digit - 10)


def add_numbers(x, y, base=10):
    """
    Adds two numbers
    x: Number
    y: Number
    base: int
    :return: Number
    """

    result = Number()

    carry = 0

    for i in range(max(len(x.digits), len(y.digits))):
        digit_x = x.digits[i] if i < len(x.digits) else '0'
        digit_y = y.digits[i] if i < len(y.digits) else '0'

        digit_x = convert_char_to_digit(digit_x)
        digit_y = convert_char_to_digit(digit_y)

        digit_sum = digit_x + digit_y + carry

        carry = digit_sum // base
        digit_sum = digit_sum % base

        result.digits[i] = convert_digit_to_char(digit_sum)

    result.number_of_digits = len(str(result))

    return result


def sub_numbers(x, y, base=10):
    """
    Subtracts two numbers
    x: Number
    y: Number
    base: int
    :return: Number
    """

    result = Number()

    carry = 0

    for i in range(max(len(x.digits), len(y.digits))):
        digit_x = x.digits[i] if i < len(x.digits) else '0'
        digit_y = y.digits[i] if i < len(y.digits) else '0'

        digit_x = convert_char_to_digit(digit_x)
        digit_y = convert_char_to_digit(digit_y)

        digit_sub = digit_x - digit_y - carry

        if digit_sub < 0:
            carry = 1
            digit_sub += base
        else:
            carry = 0

        result.digits[i] = convert_digit_to_char(digit_sub)

    result.number_of_digits = len(str(result))

    return result


def multiply_by_digit(x, digit, base=10):
    """
    Multiplies a number by a digit
    x: Number
    digit: int
    base: int
    :return: Number
    """

    result = Number()

    carry = 0

    for i in range(len(x.digits)):
        digit_x = convert_char_to_digit(x.digits[i])

        digit_mul = digit_x * digit + carry

        carry = digit_mul // base
        digit_mul = digit_mul % base

        result.digits[i] = convert_digit_to_char(digit_mul)

    result.number_of_digits = len(str(result))

    return result


def divide_by_digit(x, digit, base=10):
    """
    Divides a number by a digit
    x: Number
    digit: int
    base: int
    return: Number
    """

    # special case for digit == 0
    if digit == 0:
        raise ValueError('Division by zero')

    result = Number()

    remainder = 0

    for i in range(len(x.digits) - 1, -1, -1):
        digit_x = convert_char_to_digit(x.digits[i])

        remainder = x.base * remainder + digit_x
        result.digits[i] = convert_digit_to_char(remainder // digit)
        remainder = remainder % digit

    result.number_of_digits = len(str(result))

    return result


def convert_number(number, destination_base):
    """
    Converts a number from one base to another
    number: Number
    source_base: int
    destination_base: int
    :return: Number
    """

    # special case for destination_base == 0
    if destination_base == 0:
        raise ValueError('Destination base cannot be zero')

    # special case for number == 0
    if number == '0':
        return Number('0')

    # convert number to base 10
    number_in_base_10 = number.to_base_10()

    # convert number from base 10 to destination base
    number_in_destination_base = []

    while number_in_base_10 > 0:
        remainder = number_in_base_10 % destination_base
        number_in_base_10 = number_in_base_10 // destination_base
        number_in_destination_base += convert_digit_to_char(remainder)

    result = number_in_destination_base[::-1]
    result = ''.join(result)
    result = Number(result)

    return result
