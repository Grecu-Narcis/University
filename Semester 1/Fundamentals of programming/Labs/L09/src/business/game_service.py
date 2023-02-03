from src.business.service_exceptions import WrongPlaceException


class GameService:
    def __init__(self, repository):
        self.repo = repository
        self.player = '😎'

    def play_move(self, row, column):
        """
        Function to play a move.
        :param row: int
        :param column: int
        :return: None
        """

        if not self.is_in_board(row, column):
            raise WrongPlaceException

        if self.get_position(row, column) != '':
            raise WrongPlaceException('Position is unavailable!')

        self.repo.set(row, column, self.player)
        self.block_neighbours(row, column)

        self.player = '😎' if self.player == '😋' else '😋'

    @staticmethod
    def is_in_board(row, column):
        """
        Function to check if a given position is inside the board.
        :param row: int
        :param column: int
        :return: True if the position is in board, False otherwise
        """
        return 0 <= row <= 5 and 0 <= column <= 5

    def is_empty(self, row, column):
        """
        Function to check if a position is empty.
        :param row: int
        :param column: int
        :return: True if the position is empty, False otherwise
        """
        return self.repo.get_position(row, column) == ''

    def block_neighbours(self, row, column):
        """
        Function to block neighbours after a move.
        :param row: int
        :param column: int
        :return: list, representing blocked neighbours
        """

        dx = [-1, -1, -1, 0, 1, 1,  1,  0]
        dy = [-1,  0,  1, 1, 1, 0, -1, -1]

        blocked = []

        for i in range(8):
            new_row = row + dx[i]
            new_column = column + dy[i]

            if self.is_in_board(new_row, new_column) is True and self.get_position(new_row, new_column) == '':
                self.repo.set(new_row, new_column, '💩')
                blocked.append((new_row, new_column))

        return blocked

    def check_for_win(self):
        """
        Function to check if the game is over.
        :return: True if there are no more empty positions available, False otherwise
        """

        for i in range(6):
            for j in range(6):
                if self.repo.get_position(i, j) == '':
                    return False

        return '😎' if self.player == '😋' else '😋'

    def get_position(self, row, column):
        return self.repo.get_position(row, column)

    def get_player(self):
        return self.player

    def empty_neigh(self, row, column):
        """
        Function to count how many empty neighbours a position has
        :param row: int
        :param column: int
        :return: int, number of the empty neighbours
        """

        dx = [-1, -1, -1, 0, 1, 1, 1, 0]
        dy = [-1, 0, 1, 1, 1, 0, -1, -1]

        counter = 0

        for i in range(8):
            new_row = row + dx[i]
            new_column = column + dy[i]

            if self.is_in_board(new_row, new_column) is True and self.get_position(new_row, new_column) == '':
                counter += 1

        return counter

    def next_move(self):
        """
        Function to compute next move of the computer
        :return: list, representing the move of the computer
        """

        best_move = [-1, -1]
        most_empty_neighbours = 0
        for i in range(6):
            for j in range(6):
                if self.get_position(i, j) == '':
                    neigh_count = self.empty_neigh(i, j)
                    if neigh_count > most_empty_neighbours:
                        most_empty_neighbours = neigh_count
                        best_move = [i, j]

        self.play_move(best_move[0], best_move[1])

        return best_move

    def get_row(self, row):
        return self.repo.get_row(row)

    def get_column(self, column):
        return self.repo.get_column(column)
