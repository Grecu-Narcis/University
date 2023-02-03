from datetime import date

from src.domain.validator_exception import ValidatorException


class Rental:
    def __init__(self, rental_id, client_id, movie_id, rented_date, due_date, returned_date):
        self._id = rental_id
        self._movie_id = movie_id
        self._client_id = client_id
        self._rented_date = rented_date
        self._due_date = due_date
        self._returned_date = returned_date

    @property
    def id(self):
        return self._id

    @property
    def movie_id(self):
        return self._movie_id

    @property
    def client_id(self):
        return self._client_id

    @property
    def rented_date(self):
        return self._rented_date

    @property
    def due_date(self):
        return self._due_date

    @property
    def returned_date(self):
        return self._returned_date

    def __len__(self):
        return (self._due_date - self._rented_date).days + 1

    def __str__(self):
        return f'ID: {self.id}, movie id: {self.movie_id}, client id: {self.client_id}, rented date: {self.rented_date}' \
               f', due date: {self.due_date}, returned date: {self.returned_date}'

    def __repr__(self):
        return str(self)


class RentalValidator:
    @staticmethod
    def validate(rental):
        if not isinstance(rental, Rental):
            raise TypeError('Can validate only Rental!')

        errors = []
        if len(rental) < 1:
            errors.append('Rental should be at least 1 day long!')

        if len(errors) > 0:
            raise ValidatorException(errors)
