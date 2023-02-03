"""

@author: radu

 
"""


# class ProductRepository:
#     def __init__(self):
#         self.__all_entities = {}
#
#     def find_all(self):
#         """
#         This method returns a list of entities
#         :return: list
#         """
#         return list(self.__all_entities.values())
#
#     def __find_by_id(self, entity_id):
#         if entity_id in self.__all_entities:
#             return self.__all_entities[entity_id]
#         return None
#
#     def save(self, product):
#         if self.__find_by_id(product.get_id()) is not None:
#             raise ValueError("Duplicate id")
#         self.__all_entities[product.get_id()] = product
#
#     # def update(self, entity_id, product):
#     #     self.__all_entities[entity_id].set_name(product.get_name())
#     #     self.__all_entities[entity_id].set_price(product.get_price())
#     def update(self, product):
#         if self.__find_by_id(product.get_id()) is None:
#             raise ValueError("Id does not exist")
#         self.__all_entities[product.get_id()] = product
#
#     def delete_by_id(self, entity_id):
#         if self.__find_by_id(entity_id) is None:
#             raise ValueError("Id does not exist")
#         del self.__all_entities[entity_id]


class GenericRepository:
    def __init__(self, validator):
        self.__all_entities = {}
        self.__validator = validator

    def find_all(self):
        """
        This method returns a list of entities
        :return: list
        """
        return list(self.__all_entities.values())

    def find_by_id(self, entity_id):
        if entity_id in self.__all_entities:
            return self.__all_entities[entity_id]
        return None

    def save(self, entity):
        self.__validator.validate(entity)
        if self.__find_by_id(entity.id) is not None:
            raise ValueError("Duplicate id")
        self.__all_entities[entity.id] = entity

    def update(self, entity):
        self.__validator.validate(entity)
        if self.__find_by_id(entity.id) is None:
            raise ValueError("Id does not exist")
        self.__all_entities[entity.id] = entity

    def delete_by_id(self, entity_id):
        if self.__find_by_id(entity_id) is None:
            raise ValueError("Id does not exist")
        del self.__all_entities[entity_id]
