import random

from src.domain.cell import Cell
from src.infrastructure.game_repo import GameRepo
from src.infrastructure.patterns_repo import PatternRepo


class GameService:
    def __init__(self, game_repo: GameRepo, pattern_repo: PatternRepo):
        self.__game_repo = game_repo
        self.__pattern_repo = pattern_repo
        self.__pattern_repo.load_file()

    def get_all(self):
        return self.__game_repo.get_all()

    def get_board(self):
        table = []
        for i in range(8):
            table.append(self.get_all()[i*8: (i+1)*8])

        return table


    def get_pattern(self, pattern_name):
        pattern = self.__pattern_repo.find_pattern(pattern_name)

        if pattern is None:
            raise ValueError('Pattern not found!')

        return pattern

    def add_pattern(self, pattern_name, x, y):
        pattern = self.get_pattern(pattern_name)
        pattern_size = len(pattern)

        if x + pattern_size > 8 or y + pattern_size > 8:
            raise ValueError("Pattern can't be placed at given position!")

        for i in range(pattern_size):
            for j in range(pattern_size):
                if pattern[i][j] == '1' and self.__game_repo.get_cell(i + x, j + y).value == 'X':
                    raise ValueError('Live cell overlap!')

        for i in range(pattern_size):
            for j in range(pattern_size):
                if pattern[i][j] == '1':
                    self.__game_repo.set_cell(i + x, j + y, 'X')

    def get_neighbours(self, cell: Cell):
        dx = [-1, -1, -1, 0, 1, 1,  1,  0]
        dy = [-1,  0,  1, 1, 1, 0, -1, -1]

        neighbours_count = 0

        for i in range(8):
            new_x = cell.row + dx[i]
            new_y = cell.column + dy[i]

            neigh_cell = self.__game_repo.get_cell(new_x, new_y)
            if neigh_cell is not None and neigh_cell.value == 'X':
                neighbours_count += 1

        return neighbours_count

    def __update_board_after_simulation(self, new_board):
        for i in range(8):
            for j in range(8):
                if new_board[i][j] == 1:
                    self.__game_repo.set_cell(i, j, 'X')
                else:
                    self.__game_repo.set_cell(i, j, ' ')

    def __simulate_generation(self):
        """
        Function that simulates one generation.
        For each cell counts the number of neighbours and update according to the rules.
        :return: None
        """
        new_board = []
        for i in range(8):
            row = []
            for j in range(8):
                cell = self.__game_repo.get_cell(i, j)
                neigh_count = self.get_neighbours(cell)

                if cell.value == 'X':
                    if neigh_count < 2 or neigh_count > 3:
                        row.append(0)

                    else:
                        row.append(1)

                else:
                    if neigh_count == 3:
                        row.append(1)
                    else:
                        row.append(0)

            new_board.append(row)

        self.__update_board_after_simulation(new_board)

    def simulate_n_generations(self, n):
        for i in range(n):
            self.__simulate_generation()

    def save_to_file(self, file_name):
        file = open(file_name, 'wt')

        for i in range(8):
            for j in range(8):
                cell = self.__game_repo.get_cell(i, j)
                if cell.value == 'X':
                    file.write('1 ')
                else:
                    file.write('0 ')
            file.write('\n')

        file.close()

    def load_from_file(self, file_name):
        file = open(file_name, 'rt')

        board = []

        for line in file.readlines():
            row = line.strip()
            if row == '':
                continue

            board.append(row.split())

        for i in range(8):
            for j in range(8):
                if board[i][j] == '1':
                    self.__game_repo.set_cell(i, j, 'X')
                else:
                    self.__game_repo.set_cell(i, j, ' ')

        file.close()
