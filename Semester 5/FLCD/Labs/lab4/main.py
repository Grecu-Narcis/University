from scanner.Scanner import Scanner
from prettytable import PrettyTable


def log_to_file(file_path, symbol_table, pif):
    with open(file_path, 'a') as file:
        file.write('-----------Symbol table----------\n')
        file.write(str(symbol_table))

        file.write('\n\n-------PIF---------\n')

        table = PrettyTable()
        table.field_names = ["Item", "Location"]

        for item in pif:
            table.add_row([item[0], item[1]])

        print(table, file=file)


def clear_file(file_path):
    with open(file_path, 'w') as _:
        pass


if __name__ == '__main__':
    scanner = Scanner("tokens.in")
    symbol_table, pif = scanner.parse_program("p1.txt")

    out_path = 'output.txt'

    clear_file(out_path)
    log_to_file(out_path, symbol_table, pif)

