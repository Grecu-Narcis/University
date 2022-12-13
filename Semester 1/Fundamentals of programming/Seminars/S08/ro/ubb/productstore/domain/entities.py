"""

@author: radu

 
"""


class Product:
    def __init__(self, product_id, name, price):
        self.__product_id = product_id
        self.__name = name
        self.__price = price

    def get_product_id(self):
        return self.__product_id

    def get_name(self):
        return self.__name

    def get_price(self):
        return self.__price

    def set_product_id(self, new_id):
        self.__product_id = new_id

    def set_name(self, new_name):
        self.__name = new_name

    def set_price(self, new_price):
        self.__price = new_price

    def __str__(self):
        return f'product_id = {self.__product_id}, name = {self.__name}, price = {self.__price}'
