from src.infrastructure.binary_file_repo import BinaryFileRepo
from src.infrastructure.json_file_repository import JsonFileRepo
from src.infrastructure.memory_repository import MemoryRepo
from src.infrastructure.text_file_repository import TextFileRepo
from src.services.service import StudentService
from src.services.undo_service import UndoService
from src.ui.ui import UI


def main():
    try:
        config_file = open('settings.properties', 'rt')
        line = config_file.readline().strip()

        arguments = [arg.strip() for arg in line.split('=')]

        if arguments[1] == 'memory':
            repo = MemoryRepo()
        elif arguments[1] == 'text':
            repo = TextFileRepo()
        elif arguments[1] == 'binary':
            repo = BinaryFileRepo()
        elif arguments[1] == 'json':
            repo = JsonFileRepo()
        else:
            print("repo type incorrect!\nby default repo type will be memory!")
            repo = MemoryRepo()

        undo_service = UndoService()
        service = StudentService(repo, undo_service)
        ui = UI(service)

        ui.start()

    except FileNotFoundError:
        print("no config file found!")

        repo = MemoryRepo()
        undo_service = UndoService()
        service = StudentService(repo, undo_service)
        ui = UI(service)

        ui.start()


main()
