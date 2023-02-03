import unittest

from src.domain.board import Board
from src.infrastructure.repository import Repository


class TestRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.board = Board()
        self.repo = Repository(self.board)

    def test_get_board(self):
        self.assertEqual(self.repo.get_board(), self.board)

    def test_set_position(self):
        self.repo.set(2, 3, 'X')
        self.assertEqual(self.board.get(2, 3), 'X')

    def test_get_position(self):
        self.board.set(2, 3, 'O')
        self.assertEqual(self.repo.get_position(2, 3), 'O')
        self.assertEqual(self.repo.get_position(1, 1), '-')