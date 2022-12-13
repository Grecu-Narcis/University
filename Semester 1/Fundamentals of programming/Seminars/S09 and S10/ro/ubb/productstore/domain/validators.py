"""

@author: radu

 
"""


class ProductValidator:
    def validate(self, product):
        if product.name == "":
            raise ValueError("name can not be empty")
        # todo: other validations
