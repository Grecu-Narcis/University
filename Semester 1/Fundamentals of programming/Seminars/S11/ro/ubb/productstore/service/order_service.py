"""

@author: radu

 
"""
from functools import reduce

from ro.ubb.productstore.domain.dto import OrderAssembler


class OrderService:
    def __init__(self, product_repository, order_repository):
        self.__product_repository = product_repository
        self.__order_repository = order_repository

    def get_orders_greater_than_value(self, cost: int):
        order_dtos = self.__create_order_dtos()
        # result = []
        # for order_dto in order_dtos:
        #     if order_dto.cost > cost:
        #         result.append(order_dto)
        #

        # result = [order_dto for order_dto in order_dtos if order_dto.cost > cost]

        result = filter(lambda order_dto: order_dto.cost > cost, order_dtos)

        return result

    def __create_order_dtos(self):
        all_orders = self.__order_repository.find_all()
        order_dtos = []
        for order in all_orders:
            product = self.__product_repository.find_by_id(order.product_id)
            #TODO check if the product is not None
            order_dto = OrderAssembler.create_order_dto(product, order)
            order_dtos.append(order_dto)
        return order_dtos

    def cost_of_all_orders(self):
        order_dtos = self.__create_order_dtos()
        return reduce(lambda x, y: x + y.cost, order_dtos, 0)