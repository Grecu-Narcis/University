import unittest
import pickle

from src.domain.entities import Student
from src.infrastructure.binary_file_repo import BinaryFileRepo
from src.infrastructure.memory_repository import MemoryRepo
from src.infrastructure.text_file_repository import TextFileRepo


class TestStudent(unittest.TestCase):
    def test_create_student(self):
        # test if Student constructor works
        student = Student(1, "John Doe", 913)
        self.assertEqual(student.id, 1)
        self.assertEqual(student.name, "John Doe")
        self.assertEqual(student.group, 913)


class TestMemoryRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repo = MemoryRepo()

    def test_add(self):
        # test if repo is empty initially
        self.assertEqual(len(self.repo), 0)

        student = Student(1, "John Doe", 913)
        self.repo.add(student)

        self.assertEqual(len(self.repo), 1)

        # test if repo add raises error for duplicate
        self.assertRaises(ValueError, self.repo.add, student)

    def test_find_by_id(self):
        student_id = 23

        result = self.repo.find_by_id(student_id)
        self.assertEqual(result, None)

        student = Student(student_id, 'Johny Cash', 913)
        self.repo.add(student)

        result = self.repo.find_by_id(student_id)
        self.assertEqual(result, student)

    def test_get_by_id(self):
        self.assertRaises(ValueError, self.repo.get_by_id, 101)

        student = Student(101, 'Johny Cash', 912)
        self.repo.add(student)

        result = self.repo.get_by_id(101)
        self.assertEqual(result, student)

    def test_get_all(self):
        result = self.repo.get_all()

        self.assertEqual(type(result), list)
        self.assertEqual(len(result), 0)

        student1 = Student(101, 'John', 912)
        self.repo.add(student1)

        result = self.repo.get_all()

        self.assertEqual(result, [student1])

        student2 = Student(102, 'Tommy', 917)
        self.repo.add(student2)

        result = self.repo.get_all()

        self.assertEqual(result, [student1, student2])

    def test_remove_by_id(self):
        student_id = 101
        student = Student(student_id, 'Josh Radnor', 912)

        # test if raises exception when student is not found
        self.assertRaises(ValueError, self.repo.remove_by_id, student_id)

        # test if removes when student exists
        self.repo.add(student)
        students = self.repo.get_all()
        students.remove(student)

        self.repo.remove_by_id(student_id)

        self.assertEqual(students, self.repo.get_all())


class TestTextFileRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repo = TextFileRepo()

    def test_add_to_repo(self):
        # test if repo loaded students initially
        self.assertEqual(len(self.repo), 10)

        student = Student(101, 'John Doe', 913)
        self.repo.add(student)

        self.assertEqual(len(self.repo), 11)

        # test if repo add raises error for duplicate
        self.assertRaises(ValueError, self.repo.add, student)

    def test_save_to_file(self):
        input_file = open(self.repo.file_name, 'rt')
        lines = input_file.readlines()
        input_file.close()

        # update the file to not contain student added by test_add_to_repo
        output_file = open(self.repo.file_name, 'wt')
        for line in lines[:-1]:
            output_file.write(line)
        output_file.close()

        # test if the student was saved to the file
        attributes = lines[-1].split(',')
        self.assertEqual(int(attributes[0]), 101)
        self.assertEqual(attributes[1], 'John Doe')
        self.assertEqual(int(attributes[2]), 913)

    def test_load_file(self):
        self.repo = TextFileRepo('test_file.txt')
        self.repo.load_file()


class TestBinaryFileRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repo = BinaryFileRepo()

    def test_add_to_repo(self):
        self.assertEqual(len(self.repo), 0)

        student = Student(4, 'Josh Radnor', 913)

        self.repo.add(student)
        self.assertEqual(len(self.repo), 1)

    def test_save_to_file(self):
        input_file = open(self.repo.file_name, 'rb')
        students = pickle.load(input_file)
        input_file.close()

        output_file = open(self.repo.file_name, 'wb')
        pickle.dump(students[:-1], output_file)
        output_file.close()

        self.assertEqual(students[-1].id, 4)
        self.assertEqual(students[-1].name, 'Josh Radnor')
        self.assertEqual(students[-1].group, 913)

    def test_load_file(self):
        self.repo = BinaryFileRepo('test_file.bin')
        self.repo.load_file()

        self.repo = BinaryFileRepo('no_file.bin')
        self.repo.load_file()


if __name__ == '__main__':
    unittest.main()

"""
stats:
memory_repo -> 71%
text_file_repo -> 81%
binary_file_repo -> 73%
"""
