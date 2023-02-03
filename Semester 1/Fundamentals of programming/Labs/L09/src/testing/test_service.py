import unittest

from src.business.game_service import GameService
from src.business.service_exceptions import WrongPlaceException
from src.domain.board import Board
from src.infrastructure.repository import Repository


class TestService(unittest.TestCase):
    def setUp(self) -> None:
        self.board = Board()
        self.repo = Repository(self.board)
        self.service = GameService(self.repo)

    def test_play_move(self):
        self.assertRaises(WrongPlaceException, self.service.play_move, 7, 1)
        self.assertRaises(WrongPlaceException, self.service.play_move, 2, 9)
        self.assertRaises(WrongPlaceException, self.service.play_move, 7, 7)

        self.board.set(2, 3, 'X')

        self.assertRaises(WrongPlaceException, self.service.play_move, 2, 3)
        self.service.play_move(1, 1)
        self.assertEqual(self.service.player, 'X')

    def test_is_empty(self):
        self.assertEqual(self.service.is_empty(2, 3), True)
        self.board.set(2, 3, 'X')
        self.assertEqual(self.service.is_empty(2, 3), False)

    def test_block_neighbours(self):
        position = [2, 3]
        neigh = [(1, 2), (1, 3), (1, 4), (2, 4), (3, 4), (3, 3), (3, 2), (2, 2)]
        self.assertEqual(self.service.block_neighbours(position[0], position[1]), neigh)

    def test_check_for_win(self):
        self.assertEqual(self.service.check_for_win(), False)

        self.service.play_move(1, 1)
        self.service.play_move(1, 4)
        self.service.play_move(4, 1)
        self.service.play_move(4, 4)



        self.assertEqual(self.service.check_for_win(), 'X')

    def test_get_player(self):
        self.assertEqual(self.service.get_player(), 'O')
        self.service.play_move(2, 3)

        self.assertEqual(self.service.get_player(), 'X')


    def test_empty_neigh(self):
        self.assertEqual(self.service.empty_neigh(1, 2), 8)
        self.service.play_move(1, 2)
        self.assertEqual(self.service.empty_neigh(1, 0), 2)

    def test_next_move(self):
        self.assertEqual(self.service.next_move(), [1, 1])

        self.service.play_move(4, 5)

    def test_exception_str(self):
        exception = WrongPlaceException()
        self.assertEqual(str(exception), 'Position must be inside the board!')