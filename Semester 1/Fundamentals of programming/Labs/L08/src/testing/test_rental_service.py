import datetime
import unittest

from src.domain.rental import RentalValidator
from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException
from src.services.client_rental_exception import ClientRentalException
from src.services.movie_rental_exception import MovieRentalException
from src.services.rental_exception import RentalException
from src.services.rental_service import RentalService


class TestRentalService(unittest.TestCase):
    def setUp(self) -> None:
        self.rental_validator = RentalValidator()

        self.client_repo = Repository()
        self.movie_repo = Repository()
        self.rental_repo = Repository()

        self.service = RentalService(self.rental_validator, self.rental_repo, self.client_repo, self.movie_repo)

    def test_get_all(self):
        rents = self.service.get_all()

        self.assertEqual(type(rents), list)
        self.assertEqual(len(rents), 10)

    def test_find_by_id(self):
        item = None

        for rent in self.service.get_all():
            if rent.id == 1:
                item = rent

        self.assertEqual(self.service.find_by_id(1), item)
        self.assertEqual(self.service.find_by_id(101), None)

    def test_create_rental(self):
        rental_id = 1
        client_id = 1
        movie_id = 1
        rented_date = datetime.date(2022, 2, 12)
        due_date = datetime.date(2022, 3, 17)
        return_date = datetime.date(2022, 3, 13)

        for i in range(1, 11):
            if self.service.check_for_passed_due_dates(i) is False:
                client_id = i
                break

        self.assertRaises(RepositoryException, self.service.create_rental, rental_id, client_id, movie_id,
                          rented_date, due_date, return_date)

        self.service.create_rental(101, client_id, movie_id, rented_date, due_date, return_date)
        self.assertRaises(MovieRentalException, self.service.create_rental, rental_id, client_id, movie_id,
                          rented_date, due_date, return_date)

        rental_id = 15
        client_id = 102

        self.assertRaises(ClientRentalException, self.service.create_rental, rental_id, client_id, movie_id,
                          rented_date, due_date, return_date)

        client_id = 1
        movie_id = 102

        self.assertRaises(MovieRentalException, self.service.create_rental, rental_id, client_id, movie_id,
                          rented_date, due_date, return_date)

        movie_id = 1
        for i in range(1, 11):
            if self.service.check_for_passed_due_dates(i) is True:
                client_id = i
                break

        rented_date = datetime.date(2023, 5, 9)
        due_date = datetime.date(2023, 6, 12)
        return_date = datetime.date(2024, 7, 12)

        self.assertRaises(ClientRentalException, self.service.create_rental, rental_id, client_id, movie_id,
                          rented_date, due_date, return_date)

    def test_is_movie_available(self):
        for rent_id in range(1, 11):
            self.service.delete_rental(rent_id)

        rent_id = 1
        client_id = 1
        movie_id = 1
        rented_date = datetime.date(2020, 5, 9)
        due_date = datetime.date(2020, 12, 12)
        return_date = datetime.date(2020, 8, 15)

        self.service.create_rental(rent_id, client_id, movie_id, rented_date, due_date, return_date)

        due_date = datetime.date(2020, 4, 5)
        return_date = datetime.date(2020, 5, 8)

        self.assertEqual(self.service.is_movie_available(1, rented_date, due_date, return_date), True)

    def test_return_rental(self):
        return_date = datetime.date(2020, 5, 12)

        self.assertRaises(RentalException, self.service.return_rental, 101, return_date)

        self.service.return_rental(1, return_date)


    def test_filter_rentals(self):
        filter1 = self.service.filter_rentals(1, None)

        for rent in filter1:
            self.assertEqual(rent.client_id, 1)

        filter2 = self.service.filter_rentals(None, 2)

        for rent in filter2:
            self.assertEqual(rent.movie_id, 2)

        filter3 = self.service.filter_rentals(5, 3)

        for rent in filter3:
            self.assertEqual(rent.client_id, 5)
            self.assertEqual(rent.movie_id, 3)

    def test_most_rented_movies(self):
        self.service.most_rented_movies()
        self.service.most_active_clients()
        self.service.late_rentals()


