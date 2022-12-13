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


class Number:
    def __init__(self, value='0', base=10):
        self.digits = ['0'] * 1000
        self.number_of_digits = len(value)
        self.base = base

        if value == '0':
            self.digits[0] = '0'

        else:
            index = 0
            for digit in reversed(value):
                self.digits[index] = digit
                index += 1

    def __str__(self):
        result = []
        for i in range(len(self.digits) - 1, -1, -1):
            if self.digits[i] != '0':
                result = self.digits[0:i + 1]
                break

        return str(''.join(reversed(result)))

    def to_base_10(self):
        result = 0

        for i in range(self.number_of_digits):
            digit = convert_char_to_digit(self.digits[i])
            result += digit * (self.base ** i)

        return result
