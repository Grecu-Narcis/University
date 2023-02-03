from src.domain.cell import Cell


class GameRepo:
    def __init__(self):
        self.__data = [Cell(i, j) for i in range(8) for j in range(8)]

    def get_cell(self, row, column):
        for cell in self.__data:
            if row == cell.row and column == cell.column:
                return cell

        return None

    def set_cell(self, row, column, value):
        cell = self.get_cell(row, column)

        if cell is None:
            raise ValueError('Invalid position!')

        cell.value = value


    def get_all(self):
        return self.__data
