"""

@author: radu

 
"""
from ro.ubb.productstore.domain.entities import Product
from ro.ubb.productstore.repository.in_memory_repository import GenericRepository


class ProductFileRepository(GenericRepository):
    def __init__(self, file_name, validator):
        super().__init__(validator)
        self.__file_name = file_name
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name) as f:
            for line in f:
                array = line.split(",")
                # todo: handle exceptions
                product = Product(int(array[0]), array[1], int(array[2]))

                # self.save(product)
                super().save(product)

    def save(self, product):
        super().save(product)
        # todo: handle exceptions
        with open(self.__file_name, "a") as f:
            f.write("\n" + str(product.id) + "," + product.name + "," + str(product.price))
