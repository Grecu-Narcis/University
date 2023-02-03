from src.domain.client import ClientValidator
from src.domain.movie import MovieValidator
from src.domain.rental import RentalValidator
from src.repository.repository import Repository
from src.services.client_service import ClientService
from src.services.movie_service import MovieService
from src.services.rental_service import RentalService
from src.ui.ui import UI

client_repo = Repository()
movie_repo = Repository()
rental_repo = Repository()

client_validator = ClientValidator()
movie_validator = MovieValidator()
rental_validator = RentalValidator()

rental_service = RentalService(rental_validator, rental_repo, client_repo, movie_repo)

client_service = ClientService(client_repo, rental_service, client_validator)
movie_service = MovieService(movie_repo, rental_service, movie_validator)

ui = UI(client_service, movie_service, rental_service)

ui.main_menu()
