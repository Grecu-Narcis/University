"""

@author: radu

 
"""


# class ProductRepository:
#     def __init__(self):
#         self.__all_products = {}
#
#     def find_all(self):
#         """
#         This method returns a list of entities
#         :return: list
#         """
#         return list(self.__all_products.values())
#
#     def __find_by_id(self, product_id):
#         if product_id in self.__all_products:
#             return self.__all_products[product_id]
#         return None
#
#     def save(self, product):
#         if self.__find_by_id(product.get_id()) is not None:
#             raise ValueError("Duplicate id")
#         self.__all_products[product.get_id()] = product
#
#     # def update(self, product_id, product):
#     #     self.__all_products[product_id].set_name(product.get_name())
#     #     self.__all_products[product_id].set_price(product.get_price())
#     def update(self, product):
#         if self.__find_by_id(product.get_id()) is None:
#             raise ValueError("Id does not exist")
#         self.__all_products[product.get_id()] = product
#
#     def delete_by_id(self, product_id):
#         if self.__find_by_id(product_id) is None:
#             raise ValueError("Id does not exist")
#         del self.__all_products[product_id]


class GenericRepository:
    def __init__(self, validator):
        self.__all_products = {}
        self.__validator = validator

    def find_all(self):
        """
        This method returns a list of entities
        :return: list
        """
        return list(self.__all_products.values())

    def __find_by_id(self, product_id):
        if product_id in self.__all_products:
            return self.__all_products[product_id]
        return None

    def save(self, product):
        self.__validator.validate(product)
        if self.__find_by_id(product.id) is not None:
            raise ValueError("Duplicate id")
        self.__all_products[product.id] = product

    def update(self, product):
        self.__validator.validate(product)
        if self.__find_by_id(product.id) is None:
            raise ValueError("Id does not exist")
        self.__all_products[product.id] = product

    def delete_by_id(self, product_id):
        if self.__find_by_id(product_id) is None:
            raise ValueError("Id does not exist")
        del self.__all_products[product_id]
