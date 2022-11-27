import copy

from src.infrastructure.transaction_repository import *


def create_transactions_service(transactions_repository):
    return {"repo": transactions_repository,
            "version": []}


def store_version(service):
    version = copy.deepcopy(service['repo'])
    service['version'].append(version)


def pop_version(service):
    if len(service['version']):
        service['repo'] = service['version'].pop()

    else:
        service['repo'] = []


def add_transaction_to_service(service, transaction):
    add_transaction_to_repo(service['repo'], transaction)


def remove_transaction_from_service(service, transaction):
    service['repo'] = remove_transaction_from_repo(service['repo'], transaction)


def remove_transaction_specific_day_from_service(service, day):
    service['repo'] = remove_transaction_specific_day_from_repo(service['repo'], day)


def remove_transaction_interval_days_from_service(service, start_day, end_day):
    service['repo'] = remove_transaction_interval_days_from_repo(service['repo'], start_day, end_day)


def remove_transaction_specific_type_from_service(service, transaction_type):
    service['repo'] = remove_transaction_specific_type_from_repo(service['repo'], transaction_type)


def replace_amount_for_transactions_in_service(service, day, transaction_type, description, value):
    replace_amount_for_transactions_in_repo(service['repo'], day, transaction_type, description, value)


def number_of_transactions_in_service(service):
    return number_of_transactions_in_repo(service['repo'])


def filter_transactions_by_type_from_service(service, transaction_type):
    service['repo'] = filter_transactions_by_type_from_repo(service['repo'], transaction_type)


def filter_transactions_by_type_and_value_from_service(service, transaction_type, value):
    service['repo'] = filter_transactions_by_type_and_value_from_repo(service['repo'], transaction_type, value)


def get_all_transactions_from_service(service):
    return get_all_transactions_from_repo(service['repo'])


def get_all_transactions_by_type_from_service(service, transaction_type):
    return get_all_transactions_by_type_from_repo(service['repo'], transaction_type)


def get_all_transactions_amount_less_from_service(service, amount):
    return get_all_transactions_amount_less_from_repo(service['repo'], amount)


def get_all_transactions_amount_greater_from_service(service, amount):
    return get_all_transactions_amount_greater_from_repo(service['repo'], amount)


def get_all_transactions_amount_equal_from_service(service, amount):
    return get_all_transactions_amount_equal_from_repo(service['repo'], amount)


def get_balance_from_service(service, day):
    return get_balance_from_repo(service['repo'], day)
