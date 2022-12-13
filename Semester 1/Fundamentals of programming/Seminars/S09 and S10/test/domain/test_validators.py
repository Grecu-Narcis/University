"""

@author: radu

 
"""
from unittest import TestCase

from ro.ubb.productstore.domain.entities import Product
from ro.ubb.productstore.domain.validators import ProductValidator


class TestProductValidator(TestCase):
    def test_validate(self):
        validator = ProductValidator()
        product = Product(1, "", 10)
        self.assertRaises(ValueError, validator.validate, product)
