from src.domain.client import Client
import random


class ClientService:
    def __init__(self, client_repo, rental_service, validator):
        self._repo = client_repo
        self._rental_service = rental_service
        self._validator = validator


    def find_by_id(self, id_to_search):
        clients = []
        for client in self.get_all():
            if client.id == id_to_search:
                clients.append(client)

        return clients

    def create_client(self, client_id, name):
        client = Client(client_id, name)
        self._validator.validate(client)

        return client

    def add_client(self, client_id, name):
        client = self.create_client(client_id, name)
        self._repo.store(client)

    def delete_client(self, client_id):
        client = self._repo.delete_by_id(client_id)

        rentals = self._rental_service.filter_rentals(client.id, None)

        for rent in rentals:
            self._rental_service.delete_rental(rent.id)

        return client

    def get_client_count(self):
        return len(self._repo)

    def get_all(self):
        return self._repo.get_all()

    def search_by_name(self, name_to_search):
        matched_clients = []
        name_to_search = name_to_search.lower()

        for client in self.get_all():
            client_name = client.name.lower()
            if name_to_search in client_name:
                matched_clients.append(client)

        return matched_clients

    def update(self, client_id, name):
        client = self.create_client(client_id, name)
        self._repo.update(client)
