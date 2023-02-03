from src.domain.movie import Movie
import random


class MovieService:
    def __init__(self, movie_repo, rental_service, validator):
        self._repo = movie_repo
        self._rental_service = rental_service
        self._validator = validator

    def create_movie(self, movie_id, title, description, genre):
        movie = Movie(movie_id, title, description, genre)

        self._validator.validate(movie)

        return movie


    def add_movie(self, movie_id, title, description, genre):
        movie = self.create_movie(movie_id, title, description, genre)
        self._repo.store(movie)


    def delete_movie(self, movie_id):
        movie = self._repo.delete_by_id(movie_id)

        rentals = self._rental_service.filter_rentals(None, movie_id)

        for rent in rentals:
            self._rental_service.delete_rental(rent.id)

        return movie


    def get_movie_count(self):
        return len(self._repo)


    def get_all(self):
        return self._repo.get_all()


    def search_by_id(self, id_to_search):
        matched_movies = []

        for movie in self.get_all():
            if movie.id == id_to_search:
                matched_movies.append(movie)

        return matched_movies


    def search_by_title(self, title_to_search):
        matched_movies = []
        title_to_search = title_to_search.lower()

        for movie in self.get_all():
            movie_title = movie.title.lower()

            if title_to_search in movie_title:
                matched_movies.append(movie)

        return matched_movies


    def search_by_description(self, description_to_search):
        matched_movies = []
        description_to_search = description_to_search.lower()

        for movie in self.get_all():
            movie_description = movie.description.lower()

            if description_to_search in movie_description:
                matched_movies.append(movie)

        return matched_movies


    def search_by_genre(self, genre_to_search):
        matched_movies = []
        genre_to_search = genre_to_search.lower()

        for movie in self.get_all():
            movie_genre = movie.genre.lower()

            if genre_to_search in movie_genre:
                matched_movies.append(movie)

        return matched_movies


    def update(self, movie_id, title, description, genre):
        movie = Movie(movie_id, title, description, genre)

        self._repo.update(movie)
