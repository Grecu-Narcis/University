import random
from math import gcd

from sympy import randprime


# Helper Functions
def is_prime(num):
    if num <= 1:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True


def generate_large_prime(start, end):
    while True:
        p = randprime(start, end)
        q = randprime(start, end)

        if p != q:
            return p, q


def compute_legendre_symbol(a, p):
    a = a % p
    result = pow(a, (p - 1) // 2, p)
    if result > 1:
        return -1

    return result


def char_to_bits(char):
    # Convert the character to its ASCII value
    ascii_value = ord(char)
    # Convert the ASCII value to binary (removes the '0b' prefix)
    binary_str = bin(ascii_value)[2:]
    # Pad with leading zeros to ensure it's 8 bits
    binary_str = binary_str.zfill(8)
    # Convert the binary string into a list of bits (0 or 1)
    bit_list = [int(bit) for bit in binary_str]
    return bit_list


# Goldwasser-Micali Cryptosystem Implementation
class GoldwasserMicali:
    def __init__(self, bits=16):
        self.bits = bits
        self.p, self.q = generate_large_prime(10**2, 10**3)
        self.n = self.p * self.q
        self.x = self._generate_x()

    def _generate_x(self):
        print(self.n)
        while True:
            y_candidate = random.randint(2, self.n - 1)

            if compute_legendre_symbol(y_candidate, self.p) == -1 and compute_legendre_symbol(y_candidate, self.q) == -1:
                return y_candidate

    def get_public_key(self):
        return {'n': self.n, 'x': self.x}

    def get_private_key(self):
        return {'p': self.p, 'q': self.q}

    def get_random_unit(self):
        while True:
            y_candidate = random.randint(2, self.n - 1)

            if gcd(y_candidate, self.n) == 1:
                return y_candidate

    def _encrypt_bit(self, bit):
        y_i = self.get_random_unit()

        product = (y_i ** 2) * (self.x ** bit)
        return product % self.n

    def _decrypt_bit(self, value):
        v1 = compute_legendre_symbol(value, self.p)
        v2 = compute_legendre_symbol(value, self.q)

        if v1 == -1 or v2 == -1:
            return 1

        return 0

    def encrypt_char(self, char):
        bits = char_to_bits(char)
        result = []

        for bit in bits:
            result.append(self._encrypt_bit(bit))

        return result

    def decrypt_char(self, encrypted_bits):
        bits = []

        for value in encrypted_bits:
            bits.append(self._decrypt_bit(value))

        result = 0

        for index, value in enumerate(bits[::-1]):
            result += value * pow(2, index)

        return chr(result)

    def encrypt(self, plaintext):
        ciphertext = []
        for char in plaintext:
            encrypted_char = self.encrypt_char(char)

            ciphertext.append(encrypted_char)
        return ciphertext

    def decrypt(self, ciphertext):
        plaintext = []
        for c in ciphertext:
            decrypted_char = self.decrypt_char(c)
            plaintext.append(decrypted_char)

        return ''.join(plaintext)


# Example Usage
if __name__ == "__main__":
    print(char_to_bits('a'))
    gm = GoldwasserMicali()

    public_key = gm.get_public_key()
    private_key = gm.get_private_key()

    print("Public Key:", public_key)
    print("Private Key:", private_key)

    plaintext = "hello world"
    print("Plaintext:", plaintext)

    ciphertext = gm.encrypt(plaintext)
    print("Ciphertext:", ciphertext)

    decrypted_text = gm.decrypt(ciphertext)
    print("Decrypted Text:", decrypted_text)
