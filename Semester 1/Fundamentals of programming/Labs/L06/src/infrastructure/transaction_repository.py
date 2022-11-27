from src.domain.entities import equal


def create_transactions_repository():
    """
    Function to create an empty repository
    :return: list
    """
    return []


def add_transaction_to_repo(repository, new_transaction):
    """
    Function to add a new transaction to repository
    :param repository: list
    :param new_transaction: dictionary
    :return: list, representing new repository containing new_transaction
    """
    for transaction in repository:
        if equal(transaction, new_transaction):
            raise ValueError("transaction exist!")

    repository.append(new_transaction)


def remove_transaction_from_repo(repository, transaction):
    """
    Function to remove transaction from repository
    :param repository: list
    :param transaction: dictionary
    :return: list, representing new repository with removed transaction
    """
    new_repo = []
    for item in repository:
        if not equal(item, transaction):
            new_repo.append(item)

    return new_repo


def remove_transaction_specific_day_from_repo(repository, day):
    """
    Function to remove all transactions from a specific day
    :param repository: list
    :param day: integer
    :return: new repository, without the transactions from day [day]
    """
    new_repo = []

    for transaction in repository:
        if transaction['day'] != day:
            new_repo.append(transaction)

    return new_repo


def remove_transaction_interval_days_from_repo(repository, start_day, end_day):
    """
    Function to remove all transactions from a specific day interval
    :param repository: list
    :param start_day: integer
    :param end_day: integer
    :return: new repository, without the transactions from days [start_day] <-> [end_day]
    """
    new_repo = []

    for transaction in repository:
        if transaction['day'] < start_day or transaction['day'] > end_day:
            new_repo.append(transaction)

    return new_repo


def remove_transaction_specific_type_from_repo(repository, transaction_type):
    """
    Function to remove all transactions with type [transaction_type]
    :param repository: list
    :param transaction_type: string
    :return: new repository, without the transactions with type [transaction_type]
    """
    new_repo = []

    for transaction in repository:
        if transaction['type'] != transaction_type:
            new_repo.append(transaction)

    return new_repo


def replace_amount_for_transactions_in_repo(repository, day, transaction_type, description, value):
    """
    Function to replace the amount of the transactions that match day, transaction_type, description with value
    :param repository: list
    :param day: integer
    :param transaction_type: string
    :param description: string
    :param value: integer
    :return: new repository, with modified amounts for transactions that match day, transaction_type and description
    """
    for transaction in repository:
        if transaction['day'] == day and transaction['type'] == transaction_type and transaction['description'] == description:
            transaction['amount'] = value


def number_of_transactions_in_repo(repository):
    return len(repository)


def filter_transactions_by_type_from_repo(repository, transaction_type):
    """
    Function to filter transactions by type
    :param repository: list
    :param transaction_type: string
    :return: new repositories with filtered transactions
    """
    new_repo = []

    for transaction in repository:
        if transaction['type'] == transaction_type:
            new_repo.append(transaction)

    return new_repo


def filter_transactions_by_type_and_value_from_repo(repository, transaction_type, value):
    """
    Function to filter transactions by type and value
    :param repository: list
    :param transaction_type: string
    :param value: integer
    :return: new repositories with filtered transactions
    """
    new_repo = []

    for transaction in repository:
        if transaction['type'] == transaction_type and transaction['amount'] < value:
            new_repo.append(transaction)

    return new_repo


def get_all_transactions_from_repo(repository):
    return repository


def get_all_transactions_by_type_from_repo(repository, transaction_type):
    result = []

    for transaction in repository:
        if transaction['type'] == transaction_type:
            result.append(transaction)

    return result


def get_all_transactions_amount_less_from_repo(repository, amount):
    result = []

    for transaction in repository:
        if transaction['amount'] < amount:
            result.append(transaction)

    return result


def get_all_transactions_amount_greater_from_repo(repository, amount):
    result = []

    for transaction in repository:
        if transaction['amount'] > amount:
            result.append(transaction)

    return result


def get_all_transactions_amount_equal_from_repo(repository, amount):
    result = []

    for transaction in repository:
        if transaction['amount'] == amount:
            result.append(transaction)

    return result


def get_balance_from_repo(repository, day):
    result = 0

    for transaction in repository:
        if transaction['day'] <= day:
            if transaction['type'] == 'in':
                result += transaction['amount']

            else:
                result -= transaction['amount']

    return result
