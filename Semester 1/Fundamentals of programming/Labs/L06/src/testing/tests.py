from src.business.services import *
from src.domain.entities import *
from src.infrastructure.transaction_repository import *


def test_create_transaction():
    day = 25
    amount = 1500
    type_of_transaction = 'in'
    description = 'salary'
    new_transaction = create_transaction(day, amount, type_of_transaction, description)

    assert get_day(new_transaction) == day
    assert get_amount(new_transaction) == amount
    assert get_type(new_transaction) == type_of_transaction
    assert get_description(new_transaction) == description

    assert to_str(new_transaction) == "transaction -> day: 25, amount: 1500, type: in, description: salary"


def test_equal():
    day = 25
    amount = 1500
    type_of_transaction = 'in'
    description = 'salary'
    new_transaction = create_transaction(day, amount, type_of_transaction, description)
    other_transaction = create_transaction(day, amount, type_of_transaction, description)

    assert equal(new_transaction, other_transaction) == True


def run_domain_tests():
    test_create_transaction()
    test_equal()


def run_infrastructure_tests():
    repo = create_transactions_repository()

    first_transaction = create_transaction(12, 1500, 'in', 'salary')

    # test add transaction to repo
    add_transaction_to_repo(repo, first_transaction)
    assert number_of_transactions_in_repo(repo) == 1

    # test remove transaction from repo
    repo = remove_transaction_from_repo(repo, first_transaction)
    assert number_of_transactions_in_repo(repo) == 0

    second_transaction = create_transaction(13, 100, 'out', 'food')

    add_transaction_to_repo(repo, first_transaction)
    add_transaction_to_repo(repo, second_transaction)

    # test remove all transactions from specific day
    repo = remove_transaction_specific_day_from_repo(repo, 12)
    assert number_of_transactions_in_repo(repo) == 1

    try:
        add_transaction_to_repo(repo, second_transaction)

    except ValueError as ve:
        assert str(ve) == 'transaction exist!'

    # test remove all transactions from start_day to end_day
    repo = remove_transaction_interval_days_from_repo(repo, 12, 14)
    assert number_of_transactions_in_repo(repo) == 0

    # test remove specific type
    add_transaction_to_repo(repo, first_transaction)
    add_transaction_to_repo(repo, second_transaction)
    repo = remove_transaction_specific_type_from_repo(repo, 'in')
    assert number_of_transactions_in_repo(repo) == 1

    # test replace amount of transactions
    replace_amount_for_transactions_in_repo(repo, 13, 'out', 'food', 250)
    assert repo[0]['amount'] == 250


def run_business_tests():
    repo = create_transactions_repository()
    service = create_transactions_service(repo)

    assert number_of_transactions_in_service(service) == 0

    first_transaction = create_transaction(15, 2500, 'out', 'black friday')

    add_transaction_to_service(service, first_transaction)


def run_all_tests():
    print("starting domain tests...")
    run_domain_tests()
    print("finished domain tests...")
    
    print("starting presentation tests...")
    run_infrastructure_tests()
    print("finished presentation tests...")

    print("starting business tests...")
    run_business_tests()
    print("finished business tests...")
    
    
