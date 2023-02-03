def create_product(product_name, quantity, item_price):
    """
    function to create a product represented as a dictionary
    :param product_name: string
    :param quantity: int
    :param item_price: int
    :return: dictionary representing the product
    """
    return {
        "product_name": product_name,
        "quantity": quantity,
        "item_price": item_price
    }


def get_product_name(product):
    return product["product_name"]


def get_quantity(product):
    return product["quantity"]


def get_price(product):
    return product["item_price"]


def add_product(product_list, product_name, quantity, item_price):
    """
    function to add a product to a list of products
    :param product_list: list
    :param product_name: string
    :param quantity: int
    :param item_price: int
    :return:
    """
    if check_if_product_exists(product_list, product_name) is True:
        return

    product = create_product(product_name, quantity, item_price)
    product_list.append(product)


def check_if_product_exists(product_list, product_name):
    for product in product_list:
        if get_product_name(product) == product_name:
            return True

    return False


def remove_product(product_list, product_name):
    new_product_list = []

    for product in product_list:
        if get_product_name(product) != product_name:
            new_product_list.append(product)

    return new_product_list


def get_all_products_in_descending_order(product_list):
    new_list = sorted(product_list, reverse=True, key=get_product_name)
    return new_list


def compute_total(product_list):
    total_value = 0

    for product in product_list:
        total_value = total_value + get_price(product) * get_quantity(product)

    return total_value
