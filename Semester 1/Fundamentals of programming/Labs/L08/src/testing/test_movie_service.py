import unittest

from src.domain.movie import MovieValidator, Movie
from src.domain.rental import RentalValidator
from src.domain.validator_exception import ValidatorException
from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException
from src.services.movie_service import MovieService
from src.services.rental_service import RentalService


class TestMovieService(unittest.TestCase):
    def setUp(self) -> None:
        self.client_repo = Repository()
        self.movie_repo = Repository()
        self.rental_repo = Repository()
        self.movie_validator = MovieValidator()
        self.rental_validator = RentalValidator()
        self.rental_service = RentalService(self.rental_validator, self.rental_repo, self.client_repo, self.movie_repo)
        self.service = MovieService(self.movie_repo, self.rental_service, self.movie_validator)

    def test_create_movie(self):
        movie_id = 101
        title = 'John Snow'
        description = 'a few words'
        genre = 'horror'

        movie = Movie(movie_id, title, description, genre)

        self.assertEqual(movie, self.service.create_movie(movie_id, title, description, genre))

        genre = 'not a genre'
        self.assertRaises(ValidatorException, self.service.create_movie, movie_id, title, description, genre)

    def test_add_movie(self):
        movie_id = 101
        title = 'John Snow'
        description = 'a few words'
        genre = 'horror'

        self.service.add_movie(movie_id, title, description, genre)

        self.assertRaises(RepositoryException, self.service.add_movie, movie_id, title, description, genre)

    def test_delete_movie(self):
        self.assertRaises(RepositoryException, self.service.delete_movie, 101)
        movie = self.service.search_by_id(1)

        self.assertEqual(self.service.delete_movie(1), movie[0])

    def test_get_movie_count(self):
        self.assertEqual(self.service.get_movie_count(), 10)

    def test_search_by_title(self):
        result = self.service.search_by_title('Random title!')
        self.assertEqual(type(result), list)
        self.assertEqual(len(result), 0)

        self.service.add_movie(101, 'title', 'description short', 'horror')

        result = self.service.search_by_title('title')
        self.assertEqual(len(result), 1)

    def test_search_by_description(self):
        result = self.service.search_by_description('random description!')
        self.assertEqual(type(result), list)
        self.assertEqual(len(result), 0)

        result = self.service.search_by_description('description 1')
        self.assertEqual(len(result), 2)

        result = self.service.search_by_description('description 5')
        self.assertEqual(len(result), 1)

    def test_search_by_genre(self):
        counter = 0

        for movie in self.service.get_all():
            if movie.genre == 'horror':
                counter += 1

        result = self.service.search_by_genre('horror')
        self.assertEqual(len(result), counter)

    def test_update(self):
        movie_id = 101
        title = 'John Snow'
        description = 'description'
        genre = 'horror'

        self.service.add_movie(movie_id, title, description, genre)
        self.service.update(movie_id, title, 'new description', genre)

        movie = self.service.search_by_id(movie_id)

        self.assertEqual(movie[0].description, 'new description')
