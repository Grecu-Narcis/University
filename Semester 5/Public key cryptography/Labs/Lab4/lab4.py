import math

from settings import alphabet
from generator import generate_keys

reverse_alphabet = {v: k for k, v in alphabet.items()}


def get_plaintext_block_size(n: int):
    # 27 ^ k < n
    return math.floor(math.log(n, 27))


def get_ciphertext_block_size(n: int):
    # n < 27 ^ l
    return math.ceil(math.log(n, 27))


# def decompose_number(n, base=27):
#     coefficients = []
#     power = int(math.log(n, base))
#
#     for k in range(power, -1, -1):
#         coeff = n // (base ** k)
#         coefficients.append(coeff)
#         n -= coeff * (base ** k)
#
#     return coefficients


def encrypt_block(block: str, public_key: tuple):
    block_sum = 0
    power = 1
    n, e = public_key

    for ch in block[::-1]:
        block_sum += alphabet[ch] * power
        power *= 27

    # encrypt block
    encrypted_block_sum = pow(block_sum, e, n)

    l = get_ciphertext_block_size(n)
    encrypted_block = ''

    for i in range(l - 1, -1, -1):
        coefficient = encrypted_block_sum // (27 ** i)
        encrypted_block_sum = encrypted_block_sum - (coefficient * 27 ** i)

        encrypted_block += reverse_alphabet[coefficient]

    return encrypted_block


def encrypt_text(text: str, public_key: tuple):
    k = get_plaintext_block_size(public_key[0])

    if len(text) % k != 0:
        extra_chars = k - len(text) % k
        text += ' ' * extra_chars

    blocks = [text[i:i + k] for i in range(0, len(text), k)]
    ciphertext = ''

    for block in blocks:
        ciphertext += encrypt_block(block, public_key)

    return ciphertext


def decrypt_block(block: str, private_key: int, n: int):
    block_sum = 0
    power = 1

    for ch in block[::-1]:
        block_sum += alphabet[ch] * power
        power *= 27

    # decrypt block
    decrypted_block_sum = pow(block_sum, private_key, n)

    k = get_plaintext_block_size(n)
    encrypted_block = ''

    for i in range(k - 1, -1, -1):
        coefficient = decrypted_block_sum // (27 ** i)
        decrypted_block_sum = decrypted_block_sum - (coefficient * 27 ** i)

        encrypted_block += reverse_alphabet[coefficient]

    return encrypted_block


def decrypt_text(text: str, private_key: int, n: int):
    l = get_ciphertext_block_size(n)
    if len(text) % l != 0:
        extra_chars = l - len(text) % l
        text += ' ' * extra_chars

    blocks = [text[i:i + l] for i in range(0, len(text), l)]

    decrypted_text = ''

    for block in blocks:
        decrypted_text += decrypt_block(block, private_key, n)

    return decrypted_text


def validate(initial_message):
    for ch in initial_message:
        if ch not in alphabet:
            return False

    return True


def main():
    n, e, d = generate_keys(10**4, 10**5)
    public_key = (n, e)
    private_key = d

    print(public_key, private_key)

    initial_message = 'diana'

    if not validate(initial_message):
        print('cannot encrypt')
        return 0

    message = encrypt_text(initial_message, public_key)
    print(f'Encrypted is: {message}')

    if validate(message) == 0:
        print('cannot decrypt')
        return 0

    print(decrypt_text(message, private_key, n))

    return 1


if __name__ == '__main__':
    for i in range(10000):
        print(i)
        if main() == 0:
            raise Exception('probleme')
