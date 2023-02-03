import unittest

from src.domain.client import Client
from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException


class TestRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.__repo = Repository()

    def test_add(self):
        self.assertEqual(len(self.__repo), 0, 'Repo is not empty at the beginning!')

        client = Client(1, 'John Doe')
        self.__repo.store(client)

        self.assertEqual(len(self.__repo), 1)

        self.assertRaises(RepositoryException, self.__repo.store, client)

    def test_find(self):
        self.assertEqual(self.__repo.find(5), None, 'Found item that does not exist!')

        client = Client(1, 'John Doe')
        self.__repo.store(client)

        self.assertEqual(self.__repo.find(1), client)

    def test_get_all(self):
        client1 = Client(1, 'John Doe')
        client2 = Client(2, 'Barry Allen')

        clients = self.__repo.get_all()

        self.assertEqual(type(clients), list, 'Get all method does not return a list!')
        self.assertEqual(len(clients), 0)

        self.__repo.store(client1)

        clients = self.__repo.get_all()
        self.assertEqual(len(clients), 1)
        self.assertEqual(clients, [client1])

        self.__repo.store(client2)

        clients = self.__repo.get_all()
        self.assertEqual(len(clients), 2)
        self.assertEqual(clients, [client1, client2])

    def test_delete_by_id(self):
        self.assertRaises(RepositoryException, self.__repo.delete_by_id, 5)

        client1 = Client(1, 'John Doe')
        self.__repo.store(client1)

        client_deleted = self.__repo.delete_by_id(1)

        self.assertEqual(client_deleted, client1)

    def test_update(self):
        client = Client(1, 'John Doe')

        self.assertRaises(RepositoryException, self.__repo.update, client)

        self.__repo.store(client)
        self.__repo.update(Client(1, 'Barry Allen'))

        client_updated = self.__repo.find(1)

        self.assertEqual(client_updated.id, 1)
        self.assertEqual(client_updated.name, 'Barry Allen')


class TestRepoException(unittest.TestCase):
    def test_get_message(self):
        repo_exception = RepositoryException('test')
        self.assertEqual(repo_exception.get_message(), 'test')

    def test_str(self):
        repo_exception = RepositoryException('test')
        self.assertEqual(str(repo_exception), 'test')


if __name__ == '__main__':
    unittest.main()
