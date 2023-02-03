from datetime import datetime

from src.domain.validator_exception import ValidatorException
from src.repository.repository_exception import RepositoryException
from src.services.rental_exception import RentalException


class UI:
    def __init__(self, client_service, movie_service, rental_service):
        self.__client_service = client_service
        self.__movie_service = movie_service
        self.__rental_service = rental_service

    def client_option_1(self):
        client_id = input('Enter client id: ')
        client_name = input('Enter client name: ')

        try:
            client_id = int(client_id)
        except ValueError:
            print('ID must be an integer!')

        try:
            self.__client_service.add_client(client_id, client_name)
        except ValidatorException as ve:
            print(str(ve))

        except RepositoryException as re:
            print(str(re))

    def client_option_2(self):
        client_id = input('Enter client id: ')

        try:
            client_id = int(client_id)
        except ValueError:
            print('Client id must be an integer!')

        try:
            self.__client_service.delete_client(client_id)
        except RepositoryException as re:
            print(str(re))

    def client_option_3(self):
        client_id = input('Enter client id to update: ')
        client_name = input('Enter new client name: ')

        try:
            client_id = int(client_id)
        except ValueError:
            print('Client id must be an integer!')

        try:
            self.__client_service.update(client_id, client_name)
        except ValidatorException as ve:
            print(str(ve))

        except RepositoryException as re:
            print(str(re))

    def client_menu(self):
        while True:
            print('Press 1 to add a client.\n'
                  'Press 2 to remove a client.\n'
                  'Press 3 to update a client.\n'
                  'Press 4 to list all clients.\n'
                  'Press 5 to go back to main menu.\n')

            option = input('Your option: ')

            if option == '1':
                self.client_option_1()

            elif option == '2':
                self.client_option_2()

            elif option == '3':
                self.client_option_3()

            elif option == '4':
                print(self.__client_service.get_all())

            elif option == '5':
                break

            else:
                print('Invalid command!')

    def movie_option_1(self):
        movie_id = input('Enter movie id: ')
        title = input('Enter movie title: ')
        description = input('Enter movie description: ')
        genre = input('Enter movie genre: ')

        try:
            movie_id = int(movie_id)
        except ValueError:
            print('ID must be a positive integer!')

        try:
            self.__movie_service.add_movie(movie_id, title, description, genre)
        except ValidatorException as ve:
            print(str(ve))

        except RepositoryException as re:
            print(str(re))

    def movie_option_2(self):
        movie_id = input('Enter movie id: ')

        try:
            movie_id = int(movie_id)
        except ValueError:
            print('ID must be a positive integer!')

        try:
            self.__movie_service.delete_movie(movie_id)
        except RepositoryException as re:
            print(str(re))

    def movie_option_3(self):
        movie_id = input('Enter movie id: ')
        title = input('Enter new title: ')
        description = input('Enter new description: ')
        genre = input('Enter new genre: ')

        try:
            movie_id = int(movie_id)
        except ValueError:
            print('ID must be a positive integer!')

        try:
            self.__movie_service.update(movie_id, title, description, genre)
        except ValidatorException as ve:
            print(str(ve))
        except RepositoryException as re:
            print(str(re))

    def movie_menu(self):
        while True:
            print('Press 1 to add a movie.\n'
                  'Press 2 to remove a movie.\n'
                  'Press 3 to update a movie. \n'
                  'Press 4 to list all movies.\n'
                  'Press 5 to go back to main menu.\n')

            option = input('Your option is: ')

            if option == '1':
                self.movie_option_1()

            elif option == '2':
                self.movie_option_2()

            elif option == '3':
                self.movie_option_3()

            elif option == '4':
                print(self.__movie_service.get_all())

            elif option == '5':
                break

            else:
                print('Invalid option!')

    def rental_option_1(self):
        rental_id = input('Enter rental id: ')
        client_id = input('Enter client id: ')
        movie_id = input('Enter movie id: ')

        rented_date = input('Enter rented date (YYYY MM DD): ')
        due_date = input('Enter due date (YYYY MM DD): ')
        returned_date = input('Enter returned date (YYYY MM DD): ')

        try:
            rental_id = int(rental_id)
            client_id = int(client_id)
            movie_id = int(movie_id)
        except ValueError:
            print('IDs must be positive integers!')

        try:
            rented_date = datetime.strptime(rented_date, '%Y %m %d').date()
            due_date = datetime.strptime(due_date, '%Y %m %d').date()
            returned_date = datetime.strptime(returned_date, '%Y %m %d').date()
        except ValueError as ve:
            print(str(ve))

        try:
            self.__rental_service.create_rental(rental_id, client_id, movie_id, rented_date, due_date, returned_date)
        except Exception as e:
            print(str(e))

    def rental_option_2(self):
        rental_id = input('Enter rental id to return: ')
        return_date = input('Enter return date of rental (YYYY MM DD): ')

        try:
            rental_id = int(rental_id)
            return_date = datetime.strptime(return_date, '%Y %m %d').date()
            self.__rental_service.return_rental(rental_id, return_date)
        except ValueError as ve:
            print(str(ve))

        except RentalException as re:
            print(str(re))

        except RepositoryException as re:
            print(str(re))

    def rental_menu(self):
        while True:
            print('Press 1 to rent a movie.\n'
                  'Press 2 to return a movie.\n'
                  'Press 3 to list all rentals.\n'
                  'Press 4 to go back to main menu.\n')

            option = input('Your option is: ')

            if option == '1':
                self.rental_option_1()

            elif option == '2':
                self.rental_option_2()

            elif option == '3':
                print(self.__rental_service.get_all())

            elif option == '4':
                break

            else:
                print('Incorrect option!')

    def client_search_menu(self):
        print('Press 1 to search by id.\n'
              'Press 2 to search by name.\n')

        option = input('Your option is: ')

        if option == '1':
            client_id = input('Enter client id you want to search for: ')

            try:
                client_id = int(client_id)
                clients = self.__client_service.find_by_id(client_id)

                if len(clients) == 0:
                    print('No matched clients!')

                else:
                    print('Clients matched: ', clients)

            except ValueError as ve:
                print('ID must be a positive integer!')

        elif option == '2':
            client_name = input('Enter client name you want to search for: ')
            clients = self.__client_service.search_by_name(client_name)

            if len(clients) == 0:
                print('No matched clients!')

            else:
                print('Clients matched: ', clients)

        else:
            print('Invalid option!')

    def movie_search_menu(self):
        print('Press 1 to search by id.\n'
              'Press 2 to search by title.\n'
              'Press 3 to search by description.\n'
              'Press 4 to search by genre.\n')

        option = input('Your option is: ')

        if option == '1':
            movie_id = input('Enter movie id you want to search by: ')
            try:
                movie_id = int(movie_id)
                movies = self.__movie_service.search_by_id(movie_id)

                if len(movies) == 0:
                    print('No movie matched!')
                else:
                    print('Matched movies: ', movies)

            except ValueError as ve:
                print('ID must be a positive integer!')

        elif option == '2':
            title = input('Enter title you want to search by: ')

            movies = self.__movie_service.search_by_title(title)

            if len(movies) == 0:
                print('No movies matched!')

            else:
                print('Matched movies: ', movies)

        elif option == '3':
            description = input('Enter the description you want to search by: ')
            movies = self.__movie_service.search_by_description(description)

            if len(movies) == 0:
                print('No movies matched!')

            else:
                print('Matched movies: ', movies)

        elif option == '4':
            genre = input('Enter the genre you want to search by: ')
            movies = self.__movie_service.search_by_genre(genre)

            if len(movies) == 0:
                print('No movies matched!')

            else:
                print('Matched movies: ', movies)


    def statistics_menu(self):
        while True:
            print('Press 1 for most rented movies.\n'
                  'Press 2 for most active clients.\n'
                  'Press 3 for late rentals.\n'
                  'Press 4 to go back to main menu.\n')

            option = input('Your option is: ')

            if option == '1':
                print(self.__rental_service.most_rented_movies())

            elif option == '2':
                print(self.__rental_service.most_active_clients())

            elif option == '3':
                print(self.__rental_service.late_rentals())

            elif option == '4':
                break

            else:
                print('Invalid option!')

    def main_menu(self):
        while True:
            print('Press 1 to manage clients.\n'
                  'Press 2 to manage movies.\n'
                  'Press 3 for rental menu.\n'
                  'Press 4 to search for a client.\n'
                  'Press 5 to search for a movie.\n'
                  'Press 6 for statistics menu.\n'
                  'Press 7 to exit.\n')

            option = input('Your option: ')

            if option == '1':
                self.client_menu()

            elif option == '2':
                self.movie_menu()

            elif option == '3':
                self.rental_menu()

            elif option == '4':
                self.client_search_menu()

            elif option == '5':
                self.movie_search_menu()

            elif option == '6':
                self.statistics_menu()

            elif option == '7':
                break

            else:
                print('Invalid option!')
