"""

@author: radu

 
"""
from random import Random


class Console:
    def __init__(self, product_service):
        self.__product_service = product_service

    def run_console(self):
        self.__add_products()
        self.__print_all_products()

    def __add_products(self):
        self.__product_service.add_product(Random().randint(1, 1000), "cehifh", 10)
        self.__product_service.add_product(Random().randint(1, 1000), "cehifh", 10)
        # todo: handle exceptions

    def __print_all_products(self):
        print(*self.__product_service.get_all(), sep="\n")
