from src.domain.entities import Student
from copy import deepcopy


class MemoryRepo:
    def __init__(self):
        self._data = {}

    def find_by_id(self, id):
        for student in self._data.values():
            if student.id == id:
                return student

        return None

    def add(self, new_student: Student):
        """
        Adds a given student to a repo if it does not exist already
        :param new_student: Student
        :return: None
        """
        if self.find_by_id(new_student.id) is not None:
            raise ValueError("Student already exists!")

        self._data[new_student.id] = new_student

    def get_by_id(self, student_id: int):
        if self.find_by_id(student_id) is None:
            raise ValueError("Student id does not exists!")

        return self._data[student_id]

    def get_all(self):
        return list(self._data.values())

    def remove_by_id(self, student_id):
        if self.find_by_id(student_id) is None:
            raise ValueError("Student doesn't exists!")

        del self._data[student_id]

    def __len__(self):
        return len(self._data)

