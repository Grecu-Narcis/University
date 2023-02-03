from src.domain.validator_exception import ValidatorException


class Client:
    def __init__(self, client_id, name):
        self._id = client_id
        self._name = name

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    def __eq__(self, other):
        if not isinstance(other, Client):
            return False

        return self.id == other.id

    def __str__(self):
        return f'Id: {self.id}, name: {self._name}'

    def __repr__(self):
        return str(self)


class ClientValidator:
    @staticmethod
    def validate(client):
        errors = []

        if client.id < 0:
            errors.append('Id must be natural number!')

        if len(client.name) == 0:
            errors.append('Client must have a name!')

        if len(errors) > 0:
            raise ValidatorException(errors)
