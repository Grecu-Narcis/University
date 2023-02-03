"""

@author: radu

 
"""
from dataclasses import dataclass


@dataclass
class OrderDTO:
    product_name: str
    quantity: int
    cost: int


class OrderAssembler:
    @staticmethod
    def create_order_dto(product, order):
        return OrderDTO(product.name, order.quantity, product.price * order.quantity)

