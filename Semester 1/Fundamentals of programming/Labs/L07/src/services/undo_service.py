class UndoService:
    def __init__(self):
        self.__history = []

    def add_command(self, command):
        self.__history.append(command)
        pass

    def undo(self, repo):
        if len(self.__history) == 0:
            return

        command = self.__history.pop()

        if type(command) == list:
            self.undo_filter(command, repo)

        else:
            self.undo_add(command, repo)

    @staticmethod
    def undo_add(student_id, repo):
        repo.remove_by_id(student_id)

    @staticmethod
    def undo_filter(students, repo):
        for student in students:
            repo.add(student)
