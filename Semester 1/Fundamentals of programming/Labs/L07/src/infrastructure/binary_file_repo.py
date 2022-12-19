import pickle

from src.domain.entities import Student
from src.infrastructure.memory_repository import MemoryRepo


class BinaryFileRepo(MemoryRepo):
    def __init__(self, file_name='file.bin'):
        super().__init__()

        self.file_name = file_name
        self.load_file()

    def add(self, student: Student):
        super().add(student)
        self.save_file()

    def load_file(self):
        try:
            input_file = open(self.file_name, 'rb')
        except IOError:
            return

        try:
            students = pickle.load(input_file)

            for student in students:
                super().add(student)
        except EOFError:
            input_file.close()
            return

        input_file.close()

    def save_file(self):
        out_file = open(self.file_name, 'wb')
        pickle.dump(self.get_all(), out_file)

        out_file.close()

    def remove_by_id(self, student_id):
        super().remove_by_id(student_id)
        self.save_file()
