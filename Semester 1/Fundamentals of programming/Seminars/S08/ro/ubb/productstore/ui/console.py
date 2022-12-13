"""

@author: radu

 
"""


class Console:
    def __init__(self, product_service):
        self.__product_service = product_service

    def run_console(self):
        self.__add_products()
        self.__print_all_products()

    def __add_products(self):
        self.__product_service.add_product(1, "p1", 79)
        self.__product_service.add_product(2, "p2", 779)

    def __print_all_products(self):
        print(self.__product_service.list_all_products())  # todo: !!!!????
