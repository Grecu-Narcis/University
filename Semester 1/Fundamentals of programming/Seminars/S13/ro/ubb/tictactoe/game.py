"""

@author: radu

 
"""


class Game:
    def __init__(self, board, player1, player2):
        self.__board = board
        self.__player1 = player1
        self.__player2 = player2

        self.__last_move = None

    def play(self):
        while True:
            if self.__move(self.__player1, 1):
                break
            if self.__move(self.__player2, 2):
                break

    # def __move(self, player, value):
    #     line, column = -1, -1
    #     if type(player) is Human:
    #         self.__draw_board()
    #         line, column = self.__read_data()
    #     self.__last_move = player.move(line, column, value)
    #     winner = self.__is_winner()
    #     if self.__is_over(self.__last_move) or winner:
    #         self.__show_game_over_status()
    #         return True
    #     return False
