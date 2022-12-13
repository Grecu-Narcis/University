"""

@author: radu

 
"""
from ro.ubb.productstore.domain.entities import Product


class ProductService:
    def __init__(self, product_repository):
        self.__product_repository = product_repository

    def add_product(self, product_id, name, price):
        product = Product(product_id,name,price)
        self.__product_repository.save(product)

    def get_all(self):
        return self.__product_repository.find_all()
