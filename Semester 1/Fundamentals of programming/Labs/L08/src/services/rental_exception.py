class RentalException(Exception):
    def __init__(self, message):
        self.__message = message

    def __str__(self):
        return str(self.__message)


# 72%
