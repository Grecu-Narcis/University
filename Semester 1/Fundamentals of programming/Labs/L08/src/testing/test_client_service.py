import unittest

from src.domain.client import ClientValidator, Client
from src.domain.rental import RentalValidator
from src.domain.validator_exception import ValidatorException
from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException
from src.services.client_service import ClientService
from src.services.rental_service import RentalService


class TestClientService(unittest.TestCase):
    def setUp(self) -> None:
        self.client_repo = Repository()
        self.movie_repo = Repository()
        self.rental_repo = Repository()
        self.client_validator = ClientValidator()
        self.rental_validator = RentalValidator()
        self.rental_service = RentalService(self.rental_validator, self.rental_repo, self.client_repo, self.movie_repo)
        self.service = ClientService(self.client_repo, self.rental_service, self.client_validator)


    def test_find_by_id(self):
        clients = self.service.find_by_id(23)
        self.assertEqual(type(clients), list, 'Find function does not return list!')
        self.assertEqual(len(clients), 0, 'Finds clients that does not match clients!')

        clients = self.service.find_by_id(1)
        self.assertEqual(len(clients), 1, 'More than one client with the same id!')


    def test_create_client(self):
        client_id = 17
        client_name = 'Grecu Narcis'

        client = self.service.create_client(client_id, client_name)

        self.assertEqual(client.id, 17)
        self.assertEqual(client.name, 'Grecu Narcis')

        self.assertRaises(ValidatorException, self.service.create_client, 21, '')
        self.assertRaises(ValidatorException, self.service.create_client, -12, 'Grecu Narcis')

    def test_add_client(self):
        client_id = 17
        client_name = 'Grecu Narcis'

        self.service.add_client(client_id, client_name)

        self.assertRaises(RepositoryException, self.service.add_client, client_id, client_name)

    def test_delete_client(self):
        client_id = 17
        client_name = 'Grecu Narcis'

        self.assertRaises(RepositoryException, self.service.delete_client, client_id)

        self.service.add_client(client_id, client_name)
        self.assertEqual(self.service.delete_client(client_id), Client(client_id, client_name))

        for i in range(1, 11):
            self.service.delete_client(i)

    def test_get_client_count(self):
        for i in range(1, 11):
            self.service.delete_client(i)

        self.assertEqual(self.service.get_client_count(), 0)

    def test_search_by_name(self):
        self.service.add_client(17, 'Grecu Narcis')

        self.assertEqual(self.service.search_by_name('Grecu Narcis'), [Client(17, 'Grecu Narcis')])
        self.assertEqual(self.service.search_by_name('Random Name'), [])

    def test_update(self):
        self.assertRaises(RepositoryException, self.service.update, 17, 'grecu narcis')

        self.service.add_client(17, 'Grecu Narcis')
        self.service.update(17, 'Grecu Narcis')

        self.assertEqual(self.service.find_by_id(17), [Client(17, 'Grecu Narcis')])
