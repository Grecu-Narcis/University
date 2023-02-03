from functions import *


def menu():
    product_list = []
    while True:
        cmd = input(">>>")
        cmd_args = cmd.split()

        if cmd_args[0] == 'add':
            if len(cmd_args) != 4:
                print("not enough parameters!")
                continue

            try:
                quantity = int(cmd_args[2])
                price = int(cmd_args[3])
            except ValueError as ve:
                print("quantity or price is not correct!")
                continue

            if int(cmd_args[2]) <= 0 or int(cmd_args[3]) <= 0:
                print("last two params are not positive integers!")
                continue

            add_product(product_list, cmd_args[1], quantity, price)

        elif cmd_args[0] == 'remove':
            if len(cmd_args) != 2:
                print("incorrect number of parameters!")
                continue

            if check_if_product_exists(product_list, cmd_args[1]) is False:
                print("product does not exist!")

            else:
                product_list = remove_product(product_list, cmd_args[1])

        elif cmd_args[0] == 'list':
            if len(cmd_args) != 2:
                print("incorrect number of parameters!")
                continue

            if cmd_args[1] == 'all':
                products = get_all_products_in_descending_order(product_list)

                print("Products are:")

                for product in products:
                    print(f'Product name: {get_product_name(product)}, price: {get_price(product)}, quantity: {get_quantity(product)}')

            elif cmd_args[1] == 'total':
                print(compute_total(product_list))

            else:
                print("incorrect parameters!")

        elif cmd_args[0] == 'exit':
            break

        else:
            print("incorrect command!")

