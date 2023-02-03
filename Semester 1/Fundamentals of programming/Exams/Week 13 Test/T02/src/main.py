from src.business.service import Service
from src.infrastructure.file_repo import FileRepo
from src.presentation.ui import UI

repo = FileRepo('input.txt')
service = Service(repo)

ui = UI(service)

ui.main_menu()
