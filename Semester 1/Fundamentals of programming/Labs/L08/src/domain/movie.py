from src.domain.validator_exception import ValidatorException


class Movie:
    def __init__(self, movie_id, title, description, genre):
        self._id = movie_id
        self._title = title
        self._description = description
        self._genre = genre

    @property
    def id(self):
        return self._id

    @property
    def title(self):
        return self._title

    @property
    def description(self):
        return self._description

    @property
    def genre(self):
        return self._genre

    def __eq__(self, other):
        if not isinstance(other, Movie):
            return False

        return self.id == other.id

    def __str__(self):
        return f'Id: {self.id}, title: {self.title}, description: {self.description}, genre: {self.genre}'

    def __repr__(self):
        return str(self)


class MovieValidator:
    def __init__(self):
        self.__genres = ['horror', 'comedy', 'drama', 'thriller', 'romance', 'animation']

    def validate(self, movie):
        if not isinstance(movie, Movie):
            raise TypeError('Can only validate movies!')

        errors = []

        if movie.genre not in self.__genres:
            errors.append('Invalid genre type! Available genres are: ' + ' '.join(self.__genres))

        if movie.id < 0:
            errors.append('ID must be a natural number!')

        if len(movie.title) == 0:
            errors.append('Movie must have title!')

        if len(movie.description) == 0:
            errors.append('Movie must have description!')

        if len(errors) > 0:
            raise ValidatorException(errors)
