from src.business.game_service import GameService
from src.domain.board import Board
from src.infrastructure.repository import Repository
from src.presentation.ui import AppUI

board = Board()
repo = Repository(board)
service = GameService(repo)

ui = AppUI(service)

ui.play_game()
