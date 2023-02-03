"""

@author: radu

 
"""
from dataclasses import dataclass


# class Product:
#
#     def __init__(self, product_id, name, price):
#         # Constructor
#         self.__product_id = product_id
#         self.__name = name
#         self.__price = price
#
#     def get_name(self):
#         return self.__name
#
#     def set_name(self, new_name):
#         self.__name = new_name
#
#     def get_id(self):
#         return self.__product_id
#
#     def set_id(self, new_id):
#         self.__product_id = new_id
#
#     def get_price(self):
#         return self.__price
#
#     def set_price(self, new_price):
#         self.__price = new_price
#
#     def __str__(self):
#         return f"{self.__product_id}. {self.__name} - {self.__price} lei"

# def __repr__(self):
#     return f"{self.__product_id}. {self.__name} - {self.__price} lei"


# class Order:
#     def __init__(self, order_id, product_id, quantity):
#         self.__order_id = order_id
#         self.__product_id = product_id
#         self.__quantity = quantity
#
#     @property
#     def order_id(self):
#         return self.__order_id
#
#     @order_id.setter
#     def order_id(self, value):
#         self.__order_id = value
#
#     @property
#     def product_id(self):
#         return self.__product_id
#
#     @product_id.setter
#     def product_id(self, value):
#         self.__product_id = value
#
#     @property
#     def quantity(self):
#         return self.__quantity
#
#     @quantity.setter
#     def quantity(self, value):
#         self.__quantity = value


@dataclass
class Product:
    __product_id: int
    name: str
    price: int

    @property
    def id(self):
        return self.__product_id


@dataclass
class Order:
    __order_id: int
    __product_id: int
    quantity: int

    @property
    def id(self):
        return self.__order_id

    @property
    def product_id(self):
        return self.__product_id
