class Board:
    def __init__(self):
        self.__board = [['' for i in range(6)] for j in range(6)]

    def set(self, row, column, value):
        self.__board[row][column] = value

    def get(self, row, column):
        return self.__board[row][column]

    def get_row(self, row):
        return self.__board[row]

    def get_column(self, column):
        return [row[column] for row in self.__board]
