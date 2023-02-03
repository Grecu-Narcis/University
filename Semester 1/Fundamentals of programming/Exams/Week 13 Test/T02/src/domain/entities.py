class Player:
    def __init__(self, id, name, strength):
        self.__id = id
        self.__name = name
        self.__strength = strength

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    @property
    def strength(self):
        return self.__strength

    @strength.setter
    def strength(self, new_strength):
        self.__strength = new_strength

    def __str__(self):
        return f'{self.id}, {self.name}, {self.strength}'

    def __repr__(self):
        return str(self)
