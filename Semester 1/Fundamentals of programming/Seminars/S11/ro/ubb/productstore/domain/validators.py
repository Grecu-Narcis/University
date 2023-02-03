"""

@author: radu

 
"""


class ProductValidator:

    @staticmethod
    def validate(product):
        if product.name == "":
            raise ValueError("name can not be empty")
        # todo: other validations - price should be int, > 0


class OrderValidator:
    @staticmethod
    def validate(order):
        pass
