from src.domain.entities import Player
from src.infrastructure.generic_repo import Repository


class FileRepo(Repository):
    def __init__(self, file_name):
        super().__init__()

        self.__file_name = file_name
        self.load_file()

    def load_file(self):
        try:
            file = open(self.__file_name, 'r')
        except IOError:
            return

        for line in file.readlines():
            fields = line.split(',')

            id = int(fields[0])
            name = fields[1]
            strength = int(fields[2])

            player = Player(id, name, strength)

            self.add(player)

        file.close()

    def save_file(self):
        file = open(self.__file_name, 'w')

        for item in self.get_all():
            file.write(f'{item.id},{item.name},{item.strength}\n')

        file.close()

    def add(self, item):
        super().add(item)

        self.save_file()

    def remove_by_id(self, item):
        super().remove_by_id(item)

        self.save_file()

    def update(self, item):
        super().update(item)

        self.save_file()
