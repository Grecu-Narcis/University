from src.business.service_exceptions import WrongPlaceException
import prettytable


class AppUI:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def get_input():
        row = input('Enter row: ')
        column = input('Enter column: ')

        try:
            row = int(row)
            column = int(column)

            return row, column

        except ValueError:
            print('Row and column must be integers between 1 and 6!')
            AppUI.get_input()

    def print_board(self):
        table = prettytable.PrettyTable()
        table.hrules = prettytable.ALL
        table.add_column('X', ['1', '2', '3', '4', '5', '6'])

        for i in range(6):
            table.add_column(str(i+1), self.__service.get_column(i))
            # table.add_row(self.__service.get_row(i))

        print(table)
        print()

    def play_game(self):
        winner = ''
        while self.__service.check_for_win() is False:
            self.print_board()
            row, column = AppUI.get_input()
            row -= 1
            column -= 1

            try:
                self.__service.play_move(row, column)
                self.print_board()

                if self.__service.check_for_win() == '😎':
                    winner = '😎'
                    break

                move = self.__service.next_move()
                print(f'Computer played at row {move[0] + 1} and column {move[1] + 1}.')
                if self.__service.check_for_win() == '😋':
                    winner = '😋'
                    break

            except WrongPlaceException as wpe:
                print(str(wpe))

        self.print_board()

        if winner == '😎':
            print('You won! 🎊🎊🎊')

        else:
            print('Computer won! 😒😒😒')
