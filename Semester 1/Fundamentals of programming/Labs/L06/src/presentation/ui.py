from src.business.services import *
from src.domain.entities import create_transaction
from src.infrastructure.transaction_repository import *


def split_command(command):
    cmd = command.strip()

    cmd = cmd.split()

    for index in range(len(cmd)):
        cmd[index] = cmd[index].strip()

    return cmd[0], cmd[1:]


def add_command(current_day, params, service):
    if len(params) == 3:
        new_transaction = create_transaction(current_day, int(params[0]), params[1], params[2])
        add_transaction_to_service(service, new_transaction)

    elif len(params) == 4:
        new_transaction = create_transaction(int(params[0]), int(params[1]), params[2], params[3])
        add_transaction_to_service(service, new_transaction)

    else:
        raise ValueError('incorrect number of parameters!')


def insert_command():
    pass


def remove_command():
    pass


def replace_command():
    pass


def filter_command():
    pass


def undo_command():
    pass


def menu():

    repo = create_transactions_repository()
    service = create_transactions_service(repo)

    current_day = 1

    commands_list = {
        'add': add_command,
        'insert': insert_command,
        'remove': remove_command,
        'replace': replace_command,
        'filter': filter_command,
        'undo': undo_command
    }

    while True:
        command = input(">>>")
        cmd_keyword, params = split_command(command)

        if cmd_keyword == 'add':
            if len(params) == 3:
                try:
                    store_version(service)
                    if params[1] != 'in' and params[1] != 'out':
                        raise ValueError('invalid type of transaction')
                    new_transaction = create_transaction(current_day, int(params[0]), params[1], params[2])
                    add_transaction_to_service(service, new_transaction)
                except Exception as e:
                    pop_version(service)
                    print(str(e))

            else:
                print("incorrect number of parameters")

        elif cmd_keyword == 'insert':
            if len(params) != 4:
                print("incorrect number of parameters")
                continue

            try:
                store_version(service)
                if params[2] != 'in' and params[2] != 'out':
                    raise ValueError('invalid type of transaction')

                current_day = int(params[0])

                new_transaction = create_transaction(int(params[0]), int(params[1]), params[2], params[3])
                add_transaction_to_service(service, new_transaction)
            except Exception as e:
                pop_version(service)
                print(str(e))

        elif cmd_keyword == 'remove':
            if len(params) == 1:
                if params[0] == 'in' or params[0] == 'out':
                    store_version(service)
                    remove_transaction_specific_type_from_service(service, params[0])

                else:
                    try:
                        store_version(service)
                        day = int(params[0])
                        remove_transaction_specific_day_from_service(service, day)
                    except Exception as e:
                        pop_version(service)
                        print(str(e))

            if len(params) == 3:
                try:
                    store_version(service)
                    start_day = int(params[0])
                    end_day = int(params[1])

                    remove_transaction_interval_days_from_service(service, start_day, end_day)

                except Exception as e:
                    pop_version(service)
                    print(str(e))

            if len(params) == 4:
                try:
                    store_version(service)
                    day = int(params[0])
                    new_amount = int(params[4])

                    replace_amount_for_transactions_in_service(service, day, params[1], params[2], new_amount)

                except Exception as e:
                    pop_version(service)
                    print(str(e))

        elif cmd_keyword == 'list':
            if len(params) == 0:
                print(get_all_transactions_from_service(service))

            elif len(params) == 1:
                if params[0] != 'in' and params[0] != 'out':
                    print("incorrect parameters!")
                print(get_all_transactions_by_type_from_service(service, params[0]))

            elif len(params) == 2:
                try:
                    amount = int(params[1])

                    if params[0] == '<':
                        print(get_all_transactions_amount_less_from_service(service, amount))

                    elif params[0] == '=':
                        print(get_all_transactions_amount_equal_from_service(service, amount))

                    elif params[0] == '>':
                        print(get_all_transactions_amount_greater_from_service(service, amount))

                    elif params[0] == 'balance':
                        print(get_balance_from_service(service, amount))

                    else:
                        print("incorrect params!")
                        continue

                except Exception as e:
                    print(str(e))

        elif cmd_keyword == 'filter':
            if len(params) == 1:
                if params[0] != 'in' and params[0] != 'out':
                    print("incorrect parameters!")
                    continue

                store_version(service)

                filter_transactions_by_type_from_service(service, params[0])

            elif len(params) == 2:
                if params[0] != 'in' and params[0] != 'out':
                    print("incorrect parameters!")
                    continue

                try:
                    store_version(service)

                    amount = int(params[1])
                    filter_transactions_by_type_and_value_from_service(service, params[0], amount)

                except Exception as e:
                    pop_version(service)
                    print(str(e))

        elif cmd_keyword == 'undo':
            pop_version(service)

        else:
            print("Incorrect command!")
