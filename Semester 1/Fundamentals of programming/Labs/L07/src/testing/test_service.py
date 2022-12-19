import unittest

from src.domain.entities import Student
from src.infrastructure.binary_file_repo import BinaryFileRepo
from src.infrastructure.memory_repository import MemoryRepo
from src.infrastructure.text_file_repository import TextFileRepo
from src.services.service import StudentService
from src.services.undo_service import UndoService


class TestService(unittest.TestCase):
    def setUp(self) -> None:
        self.undo_service = UndoService()
        self.memory_repo_service = StudentService(MemoryRepo(), self.undo_service)
        self.text_file_repo_service = StudentService(TextFileRepo('test_text_file.txt'), self.undo_service)
        self.binary_file_repo_service = StudentService(BinaryFileRepo('test_binary_file.bin'), self.undo_service)

    def test_add(self):
        # check if initially service generates sample data
        self.assertEqual(len(self.memory_repo_service.get_all_students()), 10)

        student = Student(101, 'Josh Radnor', 913)

        self.memory_repo_service.add_student(101, 'Josh Radnor', 913)
        self.assertEqual(len(self.memory_repo_service.get_all_students()), 11)

        self.assertRaises(ValueError, self.memory_repo_service.add_student, 101, 'Josh Radnor', 913)

    def test_get_all_students(self):
        self.assertEqual(type(self.memory_repo_service.get_all_students()), list)

        students = self.memory_repo_service.get_all_students()

        self.assertEqual(len(students), 10)

        self.memory_repo_service.add_student(245, 'Ana Clark', 916)
        students.append(Student(245, 'Ana Clark', 916))

        self.assertEqual(self.memory_repo_service.get_all_students(), students)

    def test_filter_by_group(self):
        self.memory_repo_service.add_student(120, 'Narcis Grecu', 913)
        self.memory_repo_service.filter_by_group(913)

        students = self.memory_repo_service.get_all_students()

        for student in students:
            self.assertNotEqual(student.group, 913)

    def test_undo(self):
        students = self.memory_repo_service.get_all_students()

        # check for undo in case of add
        self.memory_repo_service.add_student(101, 'Grecu Narcis', 913)
        self.memory_repo_service.undo()

        self.assertEqual(self.memory_repo_service.get_all_students(), students)

        # check for undo in case of filter
        students = []
        for student in self.memory_repo_service.get_all_students():
            if student.group != 913:
                students.append(student)

        self.memory_repo_service.add_student(101, 'Grecu Narcis', 913)
        self.memory_repo_service.filter_by_group(913)

        self.assertEqual(self.memory_repo_service.get_all_students(), students)


if __name__ == '__main__':
    unittest.main()
