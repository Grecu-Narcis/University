import copy
import unittest

from src.business.game_service import GameService
from src.infrastructure.game_repo import GameRepo
from src.infrastructure.patterns_repo import PatternRepo


class Test(unittest.TestCase):
    def setUp(self) -> None:
        self.__game_repo = GameRepo()
        self.__pattern_repo = PatternRepo()
        self.__service = GameService(self.__game_repo, self.__pattern_repo)

    @staticmethod
    def make_board(board):
        new_board = []
        for i in range(8):
            row = []
            for j in range(8):
                if board[i][j].value == 'X':
                    row.append(1)
                else:
                    row.append(0)

            new_board.append(row)

        return new_board

    def test_simulate_generation_1(self):
        self.__service.add_pattern('block', 0, 0)

        board = [[1, 1, 0, 0, 0, 0, 0, 0],
                 [1, 1, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0]]

        self.__service.simulate_n_generations(1)

        board_after_simulation = self.__service.get_board()

        new_board = self.make_board(board_after_simulation)

        self.assertEqual(board, new_board)

    def test_simulate_generation_2(self):
        self.__service.add_pattern('blinker', 0, 0)

        board = [[0, 1, 0, 0, 0, 0, 0, 0],
                 [0, 1, 0, 0, 0, 0, 0, 0],
                 [0, 1, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0]]

        self.__service.simulate_n_generations(1)

        board_after_simulation = self.__service.get_board()
        new_board = self.make_board(board_after_simulation)

        self.assertEqual(board, new_board)

    def test_simulate_generation_3(self):
        self.__service.add_pattern('spaceship', 0, 0)

        board = [[0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 1, 0, 0, 0, 0, 0],
                 [0, 0, 0, 1, 0, 0, 0, 0],
                 [0, 1, 1, 1, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0]]

        self.__service.simulate_n_generations(4)

        board_after_simulation = self.__service.get_board()
        new_board = self.make_board(board_after_simulation)

        self.assertEqual(board, new_board)
