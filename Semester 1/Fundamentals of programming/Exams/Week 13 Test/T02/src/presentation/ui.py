import copy

from src.business.service import Service


class UI:
    def __init__(self, service: Service):
        self.__service = service

    @staticmethod
    def print_menu():
        print("Press 1 to display players.\n"
              "Press 2 to play qualifying round.\n"
              "Press 3 to play the tournament.\n"
              "Press 4 to exit.")


    def menu_option_1(self):
        players = self.__service.sort_descending()

        print('Players are: ')

        for player in players:
            print(player)

    def menu_battle(self, pair):
        while True:
            print(f'P1: {pair[0]}\n'
                  f'P2: {pair[1]}')

            print('Enter 1 for player one to win.\n'
                  'Enter 2 for player two to win.')

            option = input('Your option is: ')

            if option == '1':
                self.__service.remove_player(pair[1])
                self.__service.update_player(pair[0])

                print('Player 1 won!')
                break

            elif option == '2':
                self.__service.remove_player(pair[0])
                self.__service.update_player(pair[1])

                print('Player 2 won!')
                break

            else:
                print('Option is not valid!')

    def menu_option_2(self):
        players = self.__service.get_players_for_qualifying()
        pairs = self.__service.make_pairs(players)

        if len(pairs) == 0:
            print('There are no qualifying rounds!')
            return

        print('Starting qualifying rounds...')

        for pair in pairs:
            self.menu_battle(pair)

        print('Qualifying rounds are over!')

    def menu_tournament_round(self, pairs):
        print(f'Last {2 * len(pairs)}')

        for pair in pairs:
            self.menu_battle(pair)

    def menu_option_3(self):
        while True:
            players = copy.deepcopy(self.__service.get_all())
            pairs = self.__service.make_pairs(players)

            if len(players) == 1:
                break

            self.menu_tournament_round(pairs)

        players = self.__service.get_all()

        print(f'Tournament has ended!\n'
              f'Winner is {players[0]}')

    def main_menu(self):
        while True:
            self.print_menu()

            option = input('Your option is: ')
            if option == '1':
                self.menu_option_1()

            elif option == '2':
                self.menu_option_2()

            elif option == '3':
                if len(self.__service.get_all()) == 0:
                    print('No tournament can be played!')
                    break

                if self.__service.check_for_qualifying():
                    self.menu_option_2()
                self.menu_option_3()

                break

            elif option == '4':
                break

            else:
                print("Invalid option!")
