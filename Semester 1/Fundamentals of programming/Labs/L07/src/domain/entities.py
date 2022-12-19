class Student:
    def __init__(self, id: int, name: str, group: int):
        self.__id = id
        self.__name = name
        self.__group = group

    def __str__(self):
        return f'student id: {self.id}, student name: {self.name}, student group: {self.group}'

    def __repr__(self):
        return f'Student(id: {self.id}, name: {self.name}, group: {self.group})'

    def __eq__(self, other):
        return self.id == other.id and self.name == other.name and self.group == other.group

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, new_id):
        self.__id = new_id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    @property
    def group(self):
        return self.__group

    @group.setter
    def group(self, new_group):
        self.__group = new_group



