from functions import *


def test_functionality_1():
    product_list = []

    add_product(product_list, "Napkins", 50, 2)
    assert len(product_list) == 1

    add_product(product_list, "watch", 20, 150)
    assert len(product_list) == 2

