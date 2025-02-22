import re

from automata.FiniteAutomata import FiniteAutomata
from ds.hashmap.HashMap import HashMap


class Scanner:
    integer_fa = FiniteAutomata('integer_fa.in')
    identifier_fa = FiniteAutomata('identifier_fa.in')

    def __init__(self, tokens_file):
        self.__tokens = Scanner.load_tokens(tokens_file)

    def parse_program(self, program_file_path):
        symbol_table = HashMap()
        pif = []
        line_count = 0

        with open(program_file_path, 'r') as program_file:
            for line in program_file.readlines():
                line = line.strip()

                if line == '':
                    continue

                line_count += 1

                self.parse_line(line, symbol_table, pif, line_count)

        return symbol_table, pif

    def parse_line(self, line, symbol_table, pif, line_count):
        line_tokens = Scanner.get_tokens_from_line(line)

        for token in line_tokens:
            if self.is_reserved_token(token):
                pif.append((token, None))

            elif Scanner.is_identifier(token) or Scanner.is_constant(token):
                position = symbol_table.add(token)
                pif.append((token, position))

            else:
                raise Exception(f"Lexical error at line: {line_count} on token: {token}")

    @staticmethod
    def get_tokens_from_line(line):
        tokens = re.split(r"(\s+|[;(){},]|={2}|[<>]=|[+\-*/=<>%]|'.*')", line)
        tokens = [token for token in tokens if token.strip()]

        return tokens

    @staticmethod
    def load_tokens(tokens_file_path):
        tokens = set()

        with open(tokens_file_path, "r") as tokens_file:
            for line in tokens_file.readlines():
                tokens.add(line.strip())

        return tokens

    def is_reserved_token(self, token):
        return token in self.__tokens

    @staticmethod
    def is_identifier(token):
        return Scanner.identifier_fa.accepts_word(token)

    @staticmethod
    def is_number(token):
        return Scanner.integer_fa.accepts_word(token)

    @staticmethod
    def is_string(token):
        return re.match("'.*'", token)

    @staticmethod
    def is_constant(token):
        return Scanner.is_number(token) or Scanner.is_string(token)
