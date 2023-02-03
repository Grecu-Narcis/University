class Repository:
    def __init__(self):
        self.__data = []

    def find_by_id(self, item_id):
        for item in self.__data:
            if item.id == item_id:
                return item

        return None

    def add(self, item):
        if self.find_by_id(item.id) is not None:
            raise ValueError('Item already in repo!')

        self.__data.append(item)

    def remove_by_id(self, item):
        item_to_remove = self.find_by_id(item.id)
        if item_to_remove is None:
            raise ValueError(f'Item with id {item.id} not in repo!')

        self.__data.remove(item_to_remove)

    def update(self, item):
        item_to_remove = self.find_by_id(item.id)
        if item_to_remove is None:
            raise ValueError(f'Item with id {item.id} not in repo!')

        self.remove_by_id(item_to_remove)
        self.add(item)

    def get_all(self):
        return self.__data

    def __len__(self):
        return len(self.__data)