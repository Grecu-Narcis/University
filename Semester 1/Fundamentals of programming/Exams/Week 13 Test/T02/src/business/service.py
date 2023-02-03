import random

from src.infrastructure.file_repo import FileRepo


class Service:
    def __init__(self, repo: FileRepo):
        self.__repo = repo

    def sort_descending(self):
        result = sorted(self.__repo.get_all(), reverse=True, key=lambda x: x.strength)

        return result

    def find_power_of_two(self):
        """
        Function to find the largest power of two <= number of players in tournament
        :return: int, representing the largest power of two <= number of players in tournament
        """
        power = 1

        while power * 2 <= len(self.__repo):
            power = power * 2

        return power

    def check_for_qualifying(self):
        """
        Function to check if there are qualifying rounds to play.
        :return: True if there are qualifying rounds to play, False otherwise.
        """
        power = self.find_power_of_two()

        if power != len(self.__repo):
            return True

        return False

    def get_players_for_qualifying(self):
        """
        Function to get the players for qualifying rounds.
        :return: list, representing the players that participate in qualifying rounds.
        """
        power = self.find_power_of_two()
        players = self.sort_descending()

        number_of_matches = len(players) - power

        return players[len(players) - 2 * number_of_matches:]

    @staticmethod
    def make_pairs(players):
        """
        Function that pairs randomly the players
        :param players: list of players
        :return: list of lists representing the pairs that plays
        """
        pairs = []

        for i in range(len(players) // 2):
            player1 = random.choice(players)
            players.remove(player1)

            player2 = random.choice(players)
            players.remove(player2)

            pairs.append([player1, player2])

        return pairs

    def update_player(self, player):
        player.strength += 1

        self.__repo.update(player)

    def remove_player(self, player):
        self.__repo.remove_by_id(player)

    def get_all(self):
        return self.__repo.get_all()
