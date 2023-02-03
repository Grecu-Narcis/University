import unittest

from src.services.client_rental_exception import ClientRentalException
from src.services.movie_rental_exception import MovieRentalException
from src.services.rental_exception import RentalException


class TestExceptions(unittest.TestCase):
    def test_client_rental_exception(self):
        exception = ClientRentalException('test')
        self.assertEqual(str(exception), 'test')

    def test_movie_rental_exception(self):
        exception = MovieRentalException('test')
        self.assertEqual(str(exception), 'test')

    def test_rental_exception(self):
        exception = RentalException('test')
        self.assertEqual(str(exception), 'test')
