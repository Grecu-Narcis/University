from src.business.game_service import GameService
from src.infrastructure.game_repo import GameRepo
from src.infrastructure.patterns_repo import PatternRepo
from src.presentation.ui import UI

game_repo = GameRepo()
pattern_repo = PatternRepo()
service = GameService(game_repo, pattern_repo)

ui = UI(service)

ui.menu()
