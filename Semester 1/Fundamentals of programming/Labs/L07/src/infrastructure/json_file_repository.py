from src.domain.entities import Student
from src.infrastructure.memory_repository import MemoryRepo
import json


class JsonFileRepo(MemoryRepo):
    def __init__(self, file_name='file.json'):
        super().__init__()

        self.file_name = file_name

        self.load_file()

    def load_file(self):
        try:
            input_file = open(self.file_name, 'r')
        except FileNotFoundError:
            return

        try:
            students = json.load(input_file)
            for student in students:
                new_student = Student(student["_Student__id"], student['_Student__name'], student['_Student__group'])
                super().add(new_student)
        except json.JSONDecodeError:
            input_file.close()

        input_file.close()

    def save_file(self):
        output_file = open(self.file_name, 'w')

        students = [student.__dict__ for student in self.get_all()]

        json.dump(students, output_file)

        output_file.close()

    def add(self, student):
        super().add(student)
        self.save_file()

    def remove_by_id(self, student_id):
        super().remove_by_id(student_id)
        self.save_file()
