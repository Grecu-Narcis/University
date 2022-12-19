import os
import random

from src.infrastructure.binary_file_repo import BinaryFileRepo
from src.domain.entities import *
from src.infrastructure.memory_repository import MemoryRepo
from src.infrastructure.text_file_repository import TextFileRepo

from src.services.undo_service import UndoService


class StudentService:
    def __init__(self, repo, undo_service):
        self.__repo = repo
        self.__undo_service = undo_service

        if type(self.__repo) == MemoryRepo:
            self.generate_students(10)

        else:
            if not os.path.isfile(self.__repo.file_name) or os.path.getsize(self.__repo.file_name) == 0:
                self.generate_students(10)

    def add_student(self, student_id: int, student_name: str, student_group: int):
        new_student = Student(student_id, student_name, student_group)

        self.__repo.add(new_student)
        self.__undo_service.add_command(student_id)

    def get_all_students(self):
        return self.__repo.get_all()

    def filter_by_group(self, group: int):
        filtered_data = {}

        for student in self.__repo.get_all():
            if student.group == group:
                filtered_data[student.id] = student

        students = list(filtered_data.values())

        for student in filtered_data.values():
            self.__repo.remove_by_id(student.id)

        self.__undo_service.add_command(students)

    def undo(self):
        self.__undo_service.undo(self.__repo)

    def generate_students(self, number_of_students: int):
        student_id = [x for x in range(1, 101)]
        student_first_name = ['John', 'Mary', 'Peter', 'Paul', 'George', 'Ringo', 'Elvis', 'Mick', 'Keith', 'Ronnie', 'Charlie']
        student_last_name = ['Smith', 'Jones', 'Williams', 'Brown', 'Taylor', 'Davies', 'Evans', 'Wilson', 'Thomas', 'Roberts']
        student_group = [911, 912, 913, 914, 915, 916, 917]

        students = []

        while number_of_students > 0:
            new_student_id = random.choice(student_id)
            student_id.remove(new_student_id)

            new_student_name = random.choice(student_first_name) + ' ' + random.choice(student_last_name)
            new_student_group = random.choice(student_group)

            students.append(Student(new_student_id, new_student_name, new_student_group))

            number_of_students -= 1

        for student in students:
            self.add_student(student.id, student.name, student.group)