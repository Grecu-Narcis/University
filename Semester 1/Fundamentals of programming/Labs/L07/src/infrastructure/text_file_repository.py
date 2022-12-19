from src.domain.entities import Student
from src.infrastructure.memory_repository import MemoryRepo


class TextFileRepo(MemoryRepo):
    def __init__(self, file_name='file.txt'):
        super().__init__()

        self.file_name = file_name

        self.load_file()

    def load_file(self):
        lines = []

        try:
            input_file = open(self.file_name, 'rt')
            for line in input_file.readlines():
                properties = line.split(',')
                student = Student(int(properties[0]), properties[1], int(properties[2]))

                super().add(student)

            input_file.close()
        except IOError:
            pass

    def save_file(self):
        out_file = open(self.file_name, 'wt')

        for student in self.get_all():
            student_string = str(student.id) + ',' + student.name + ',' + str(student.group) + '\n'
            out_file.write(student_string)
        
        out_file.close()

    def add(self, new_student):
        super().add(new_student)
        self.save_file()

    def remove_by_id(self, student_id):
        super().remove_by_id(student_id)
        self.save_file()
