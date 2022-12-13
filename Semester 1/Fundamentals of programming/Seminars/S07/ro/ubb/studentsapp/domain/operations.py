"""

@author: radu

 
"""
from ro.ubb.studentsapp.domain.entities import create_student


def add_student(all_students: list, id, name, grade):
    # todo : check for duplicate id
    student = create_student(id, name, grade)
    all_students.append(student)