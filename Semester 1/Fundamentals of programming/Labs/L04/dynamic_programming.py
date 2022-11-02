"""
Given an n * n square matrix with integer values, find the maximum length of a snake sequence.
A snake sequence begins on the matrix's top row (coordinate (0, i), 0 <= i < n).
Each element of the sequence, except the first one, must have a value ±1 from the previous one and be located directly
below, or directly to the right of the previous element. For example, element (i, j) can be
succeeded by one of the (i, j + 1) or (i + 1, j) elements.
Display the length as well as the sequence of coordinates for one sequence of maximum length.
"""


def naive_solution(board, row, column):
    """
    Function to determine the longest snake sequence in a given n*n matrix
    :param board: n*n matrix of integers
    :param row: integer, row index of the current element
    :param column:integer, column index of the current element
    :return: tuple of two elements, first is integer and represents the maximum length up to element (row, column)
             and second one is a list and represents a path for obtaining such a sequence
    """
    length_down = 0
    length_right = 0
    path_down = []
    path_right = []

    if row < len(board) - 1 and abs(board[row][column] - board[row + 1][column]) == 1:
        length_down, path_down = naive_solution(board, row + 1, column)

    if column < len(board) - 1 and abs(board[row][column] - board[row][column + 1]) == 1:
        length_right, path_right = naive_solution(board, row, column + 1)

    if length_down > length_right:
        path_down.insert(0, [row, column])
        return 1 + length_down, path_down

    else:
        path_right.insert(0, [row, column])
        return 1 + length_right, path_right


def generate_sequence(lengths, row_end, column_end):
    """
    Function to generate the path of a snake sequence
    :param lengths: n*n matrix of integers where lengths[i][j] = maximum length of a snake sequence ending at (i, j)
    :param row_end: integer, representing row index of the largest element in lengths
    :param column_end: integer, representing column index of the largest element in lengths
    :return: list, representing the snake sequence
    """
    row, column = row_end, column_end

    path = [[row, column]]

    while lengths[row][column] > 1:
        if row > 0 and lengths[row][column] == lengths[row - 1][column] + 1:
            row = row - 1

        elif column > 0 and lengths[row][column] == lengths[row][column - 1] + 1:
            column = column - 1

        path.append([row, column])

    return reversed(path)


def optimized_solution(board):
    """
    Function to find the largest snake sequence
    :param board: n*n matrix of integers
    :return: tuple of two elements, first is integer and represents the maximum length up to element (row, column)
             and second one is a list and represents a path for obtaining such a sequence
    """
    lengths = [[0 for column in range(len(board))] for row in range(len(board))]

    for column in range(len(board)):
        lengths[0][column] = 1  # any element from first row is a snake sequence of length 1

    for row in range(0, len(board)):
        for column in range(0, len(board)):
            if row > 0 and abs(board[row][column] - board[row - 1][column]) == 1 and lengths[row - 1][column] != 0:
                lengths[row][column] = max(lengths[row][column], lengths[row - 1][column] + 1)

            if column > 0 and abs(board[row][column] - board[row][column - 1]) == 1 and lengths[row][column - 1] != 0:
                lengths[row][column] = max(lengths[row][column], lengths[row][column - 1] + 1)

    print("Auxiliary data structure used looks like this in the end: ")
    for i in range(len(lengths)):
        print(lengths[i])

    row_of_max, column_of_max = 0, 0

    for row in range(len(board)):
        for column in range(len(board)):
            if lengths[row][column] > lengths[row_of_max][column_of_max]:
                row_of_max = row
                column_of_max = column

    return lengths[row_of_max][column_of_max], generate_sequence(lengths, row_of_max, column_of_max)


if __name__ == "__main__":
    size_of_matrix = int(input("Please enter the size of matrix: "))

    print ("Please enter the elements of the matrix: ")
    matrix = [[int(element) for element in input().split()] for row in range(size_of_matrix)]

    print("Optimized solution: ")

    result = optimized_solution(matrix)
    # example = [[5, 2, 3],
    #           [4, 1, 4],
    #           [5, 6, 7]]

    print("The maximum length of a snake sequence is: ", result[0])
    #
    print("An example of such a sequence is give by following coordinates: ")
    for point in result[1]:
        print(point)

    result = ()

    for column in range(len(matrix)):
        if result == () or naive_solution(matrix, 0, column)[0] > result[0]:
            result = naive_solution(matrix, 0, column)

    print("Naive solution: ")

    print("The maximum length of a snake sequence is: ", result[0])
    #
    print("An example of such a sequence is give by following coordinates: ")
    for point in result[1]:
        print(point)

