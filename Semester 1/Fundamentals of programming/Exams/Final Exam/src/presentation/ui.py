from src.business.game_service import GameService
import prettytable


class UI:
    def __init__(self, service: GameService):
        self.__service = service

    def print_board(self):
        board = self.__service.get_board()

        table = prettytable.PrettyTable()
        table.hrules = prettytable.ALL

        table.header = False

        for i in range(8):
            table.add_row(board[i])

        print(table)

    def menu(self):
        while True:
            self.print_board()

            command = input('>>>')
            command_args = command.strip().split()

            if len(command_args) < 1:
                print('Invalid command!')
                continue

            if command_args[0] == 'place':
                if len(command_args) != 3:
                    print('Invalid place command!')
                    continue

                pattern = command_args[1].strip()
                position = command_args[2].strip().split(',')

                if len(position) != 2:
                    print('Incorrect position!')
                    continue

                try:
                    position_x = int(position[0])
                    position_y = int(position[1])
                except ValueError:
                    print('Position index not integers!')
                    continue

                try:
                    self.__service.add_pattern(pattern, position_x - 1, position_y - 1)
                except ValueError as ve:
                    print(str(ve))
                    continue

            elif command_args[0] == 'tick':
                if len(command_args) == 1:
                    self.__service.simulate_n_generations(1)

                else:
                    if len(command_args) != 2:
                        print('Invalid command!')
                        continue

                    try:
                        number_of_generations = int(command_args[1])
                    except ValueError:
                        print('Number of generations must be a positive integer!')
                        continue

                    if number_of_generations < 0:
                        print('Number of generations must be a positive integer!')
                        continue

                    self.__service.simulate_n_generations(number_of_generations)

            elif command_args[0] == 'save':
                if len(command_args) != 2:
                    print('Invalid command!')
                    continue

                file_name = command_args[1]
                self.__service.save_to_file(file_name)

            elif command_args[0] == 'load':
                if len(command_args) != 2:
                    print('Invalid command!')
                    continue
                try:
                    self.__service.load_from_file(command_args[1])
                    print('File loaded successfully!')

                except IOError:
                    print('File not found!')

            elif command_args[0] == 'exit':
                break

            else:
                print('Invalid command!')