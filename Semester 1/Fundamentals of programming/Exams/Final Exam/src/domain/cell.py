class Cell:
    def __init__(self, row, column, value=' '):
        self.__row = row
        self.__column = column
        self.__value = value

    @property
    def row(self):
        return self.__row

    @property
    def column(self):
        return self.__column

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, new_value):
        self.__value = new_value

    def __str__(self):
        return str(self.__value)

    def __repr__(self):
        return str(self)
