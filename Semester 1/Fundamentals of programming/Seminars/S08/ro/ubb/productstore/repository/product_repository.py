"""

@author: radu

 
"""


class ProductRepository:
    def __init__(self):
        self.__all_products = {}

    def find_all(self):
        return list(self.__all_products.values())

    def save(self, product):
        if self.__find_by_id(product.get_product_id()) is not None:
            raise ValueError("Duplicate ID")
        self.__all_products[product.get_product_id()] = product

    def __find_by_id(self, product_id):
        if product_id in self.__all_products:
            return self.__all_products[product_id]
        return None

    def update(self, product_id, product):
        if self.__find_by_id(product_id) is None:
            raise ValueError("Id was not found!")

        self.__all_products[product_id] = product

    def delete_by_id(self, product_id):
        if self.__find_by_id(product_id) is None:
            raise ValueError("Id was not found!")

        del self.__all_products[product_id]
