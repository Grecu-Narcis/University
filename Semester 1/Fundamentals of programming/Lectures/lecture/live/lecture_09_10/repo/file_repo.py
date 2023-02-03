from lecture.live.lecture_09_10.domain.idobject import IdObject
from lecture.live.lecture_09_10.domain.ingredient import Ingredient
from lecture.live.lecture_09_10.domain.stock import Stock
from lecture.live.lecture_09_10.repo.mem_repo import Repository, RepositoryError


class FileRepo(Repository):
    def __init__(self):
        super().__init__()
        # load the file on startup
        self._load_file()

    def add(self, id_object: IdObject):
        super().add(id_object)
        # if no exceptions are raised we get here :)
        self._save_file()

    def _save_file(self):
        raise NotImplementedError()

    def _load_file(self):
        raise NotImplementedError()
