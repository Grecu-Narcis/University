class WrongPlaceException(Exception):
    def __init__(self, msg='Position must be inside the board!'):
        self.__msg = msg

    def __str__(self):
        return str(self.__msg)
