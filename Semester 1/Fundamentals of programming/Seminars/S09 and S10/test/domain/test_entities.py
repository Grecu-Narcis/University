"""

@author: radu

 
"""
from unittest import TestCase

from ro.ubb.productstore.domain.entities import Product


class TestProduct(TestCase):

    def setUp(self):
        self.product = Product(1, "p1", 10)

    def test_product_id(self):
        # product = Product(1, "p1", 10) #init data in setUp
        # self.assertEqual(product.name, "p1", "name should be p1")
        self.assertEqual(self.product.name, "p1", "name should be p1")

    def tearDown(self):
        pass  # cleanup code
