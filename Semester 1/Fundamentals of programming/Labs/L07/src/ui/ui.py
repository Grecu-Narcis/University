from src.services.service import *


class UI:
    def __init__(self, service: StudentService):
        self.__service = service

    def add_student(self):
        student_id = input("Enter student id: ")

        try:
            student_id = int(student_id)
        except ValueError:
            print("Invalid number")
            return

        student_name = input("Enter student name: ")

        student_group = input("Enter student group: ")

        try:
            student_group = int(student_group)
        except ValueError:
            print("Invalid number")
            return

        try:
            self.__service.add_student(student_id, student_name, student_group)
            print("Student successfully added!")
        except ValueError as ve:
            print(str(ve))

    def display_students(self):
        students = self.__service.get_all_students()

        for student in students:
            print(student)

    def filter_students_by_group(self):
        group = input("Enter group: ")

        try:
            group = int(group)
        except ValueError:
            print("Invalid number!")
            return

        self.__service.filter_by_group(group)

    @staticmethod
    def help_user():
        print("Press 1 to add a student.")
        print("Press 2 to display all students.")
        print("Press 3 to remove students in a group.")
        print("Press 4 to undo last operation.")
        print("Press 5 to exit.")

    def start(self):
        while True:
            self.help_user()
            choice = input(">>>")

            if choice == '1':
                self.add_student()

            elif choice == '2':
                self.display_students()

            elif choice == '3':
                self.filter_students_by_group()

            elif choice == '4':
                self.__service.undo()

            elif choice == '5':
                break

            else:
                print("Invalid choice!")