def create_transaction(day, amount, type_of_transaction, description):
    """
    create a new transaction made in day [day], with the amount of money [amount], the type of transaction is
    [type_of_transaction] (in/out) and have as description [description]

    :param day: int from [1, 30]
    :param amount: int
    :param type_of_transaction: string (in/out)
    :param description: string
    :return: a new transaction made in day [day], with the amount of money [amount], the type of transaction is
    [type] (in/out) and have as description [description]
    """
    transaction = {
        'day': day,
        'amount': amount,
        'type': type_of_transaction,
        'description': description
    }

    return transaction


def set_day(transaction, new_day):
    transaction["day"] = new_day


def get_day(transaction):
    return transaction["day"]


def set_amount(transaction, new_amount):
    transaction["amount"] = new_amount


def get_amount(transaction):
    return transaction["amount"]


def set_type(transaction, new_type):
    transaction["type"] = new_type


def get_type(transaction):
    return transaction["type"]


def set_description(transaction, new_description):
    transaction["description"] = new_description


def get_description(transaction):
    return transaction["description"]


def to_str(transaction):
    return f'transaction -> day: {transaction["day"]}, amount: {transaction["amount"]}, type: {transaction["type"]}, description: {transaction["description"]}'


def equal(transaction1, transaction2):
    if transaction1['day'] != transaction2['day']:
        return False

    if transaction1['amount'] != transaction2['amount']:
        return False

    if transaction1['type'] != transaction2['type']:
        return False

    if transaction1['description'] != transaction2['description']:
        return False

    return True
