from src.domain.board import Board


class Repository:
    def __init__(self, board):
        self.board = board

    def set(self, row, column, value):
        """
        Function to set a position to a certain value.
        :param row: int
        :param column: int
        :param value: int
        :return: None
        """
        self.board.set(row, column, value)

    def get_board(self):
        """
        Function to return the board
        :return: Board
        """
        return self.board

    def get_position(self, row, column):
        """
        Function to get the value from a certain position
        :param row: int
        :param column: int
        :return: int
        """
        return self.board.get(row, column)

    def get_row(self, row):
        return self.board.get_row(row)

    def get_column(self, column):
        return self.board.get_column(column)
