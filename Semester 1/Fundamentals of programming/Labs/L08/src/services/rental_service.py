from src.domain.client import Client
from src.domain.movie import Movie
from src.domain.rental import Rental
from src.services.client_rental_exception import ClientRentalException
from src.services.movie_rental_exception import MovieRentalException
from src.services.rental_exception import RentalException

import copy
import datetime
import random


class RentalService:
    def __init__(self, validator, rental_repo, client_repo, movie_repo):
        self._validator = validator
        self._repo = rental_repo
        self._client_repo = client_repo
        self._movie_repo = movie_repo

        self.generate_entries()


    def generate_clients(self):
        ids = [x for x in range(1, 11)]
        names = ['John', 'Mary', 'Peter', 'Paul', 'George', 'Ringo', 'Elvis', 'Mick', 'Keith', 'Ronnie']

        for i in range(10):
            client_id = random.choice(ids)
            name = random.choice(names)

            ids.remove(client_id)
            names.remove(name)

            self._client_repo.store(Client(client_id, name))


    def generate_movies(self):
        ids = [x for x in range(1, 11)]
        movie_titles = ['movie 1', 'movie 2', 'movie 3', 'movie 4', 'movie 5',
                        'movie 6', 'movie 7', 'movie 8', 'movie 9', 'movie 10']

        movie_descriptions = ['description 1', 'description 2', 'description 3', 'description 4', 'description 5',
                              'description 6', 'description 7', 'description 8', 'description 9', 'description 10']

        movie_genres = ['horror', 'comedy', 'drama', 'thriller', 'romance', 'animation']

        for i in range(10):
            movie_id = random.choice(ids)
            movie_title = random.choice(movie_titles)
            movie_description = random.choice(movie_descriptions)
            movie_genre = random.choice(movie_genres)

            ids.remove(movie_id)
            movie_titles.remove(movie_title)
            movie_descriptions.remove(movie_description)

            self._movie_repo.store(Movie(movie_id, movie_title, movie_description, movie_genre))


    def generate_entries(self):
        self.generate_clients()
        self.generate_movies()
        clients = copy.deepcopy(self._client_repo.get_all())
        movies = copy.deepcopy(self._movie_repo.get_all())

        ids = [x for x in range(1, 11)]
        rent_dates = [datetime.date(2019, 1, 1), datetime.date(2019, 1, 2), datetime.date(2019, 1, 3),
                      datetime.date(2019, 1, 4), datetime.date(2019, 1, 5), datetime.date(2019, 1, 6),
                      datetime.date(2019, 1, 7), datetime.date(2019, 1, 8), datetime.date(2019, 1, 9),
                      datetime.date(2019, 1, 10)]
        due_dates = [datetime.date(2019, 5, 2), datetime.date(2019, 5, 3), datetime.date(2019, 5, 4),
                        datetime.date(2019, 6, 5), datetime.date(2019, 8, 12), datetime.date(2019, 5, 7),
                        datetime.date(2019, 7, 22), datetime.date(2019, 5, 9), datetime.date(2019, 5, 10),
                        datetime.date(2019, 10, 11)]

        return_dates = [datetime.date(2019, 3, 12), datetime.date(2019, 4, 11), datetime.date(2019, 2, 27),
                        datetime.date(2020, 5, 1), datetime.date(2020, 7, 23), datetime.date(2019, 9, 12),
                        datetime.date(2019, 10, 23), datetime.date(2019, 4, 23), datetime.date(2019, 12, 12),
                        datetime.date(2019, 1, 23)]

        for i in range(10):
            self.create_rental(ids[i], clients[i].id, movies[i].id, rent_dates[i], due_dates[i], return_dates[i])


    def find_by_id(self, rental_id):
        for rent in self._repo.get_all():
            if rent.id == rental_id:
                return rent

        return None

    def check_for_passed_due_dates(self, client_id):
        rentals = self.filter_rentals(client_id, None)

        for rent in rentals:
            if rent.returned_date > rent.due_date:
                return True

        return False

    def create_rental(self, rental_id, client_id, movie_id, rented_date, due_date, returned_date):
        if self._client_repo.find(client_id) is None:
            raise ClientRentalException("Client doesn't exist")

        if self._movie_repo.find(movie_id) is None:
            raise MovieRentalException("Movie doesn't exist")

        rental = Rental(rental_id, client_id, movie_id, rented_date, due_date, returned_date)

        self._validator.validate(rental)

        if self.is_movie_available(movie_id, rented_date, due_date, returned_date) is False:
            raise MovieRentalException('Movie is already rented!')

        # check if client has movies
        if self.check_for_passed_due_dates(client_id) is True:
            raise ClientRentalException(f'Client with id = {client_id} has rented movies that passed their due date!')

        self._repo.store(rental)

        return rental

    def is_movie_available(self, movie_id, rented_date, due_date, returned_date):
        # check if the movie is available

        rentals = self.filter_rentals(None, movie_id)

        for rent in rentals:
            # if the movie is returned before the rent
            if due_date < rent.rented_date and returned_date < rent.rented_date:
                continue

            # if the movie is rented after it's returned by the current rent
            if rented_date > rent.due_date and rented_date > rent.returned_date:
                continue

            return False

        return True

    def return_rental(self, rental_id, return_date):
        rental = self.find_by_id(rental_id)

        if rental is None:
            raise RentalException(f'Rental with id = {rental_id} does not exist!')

        rental = self.delete_rental(rental_id)
        new_rental = Rental(rental.id, rental.client_id, rental.movie_id, rental.rented_date, rental.due_date,
                            return_date)

        self._repo.store(new_rental)

    def delete_rental(self, rental_id):
        rental = self._repo.delete_by_id(rental_id)

        return rental

    def filter_rentals(self, client_id, movie_id):
        if client_id is None:
            return [rent for rent in self._repo.get_all() if rent.movie_id == movie_id]

        if movie_id is None:
            return [rent for rent in self._repo.get_all() if rent.client_id == client_id]

        return [rent for rent in self._repo.get_all() if rent.client_id == client_id and rent.movie_id == movie_id]

    def get_all(self):
        return self._repo.get_all()

    def most_rented_movies(self):
        movies = {}

        for rental in self.get_all():
            start_date = rental.rented_date
            if rental.due_date < rental.returned_date:
                end_date = rental.returned_date

            else:
                end_date = rental.due_date

            if rental.movie_id not in movies:
                movies[rental.movie_id] = (end_date - start_date).days + 1

            else:
                movies[rental.movie_id] += (end_date - start_date).days + 1

        sorted_movies = sorted(movies.items(), reverse=True, key=lambda x: x[1])

        result = []

        for item in sorted_movies:
            movie = self._movie_repo.find(item[0])
            result.append(movie.title)

        return result

    def most_active_clients(self):
        clients = {}

        for rental in self.get_all():
            start_date = rental.rented_date

            if rental.due_date < rental.returned_date:
                end_date = rental.returned_date

            else:
                end_date = rental.due_date

            if rental.client_id not in clients:
                clients[rental.client_id] = (end_date - start_date).days + 1

            else:
                clients[rental.client_id] += (end_date - start_date).days + 1

        sorted_clients = sorted(clients.items(), reverse=True, key=lambda x: x[1])

        result = []

        for item in sorted_clients:
            client = self._client_repo.find(item[0])
            result.append(client.name)

        return result

    def late_rentals(self):
        rentals = []

        for rent in self.get_all():
            if rent.due_date > rent.returned_date:
                rentals.append(rent)

        sorted_rentals = sorted(rentals, reverse=True, key=lambda x: (x.returned_date - x.due_date).days)

        return sorted_rentals
