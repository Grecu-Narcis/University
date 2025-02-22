from automata.FiniteAutomata import FiniteAutomata


def print_menu():
    print('Enter 1 to display the set of states.')
    print('Enter 2 to display the alphabet.')
    print('Enter 3 to display the start state.')
    print('Enter 4 to display the final states.')
    print('Enter 5 to display the transitions.')
    print('Enter 6 to check if word is accepted by the automata.')
    print('Enter 0 to stop.')


def automata_demo():
    fa = FiniteAutomata('../fa.in')

    while True:
        print_menu()
        option = input('>>> ').strip()

        if option == '1':
            print(f'States: {fa.states}')

        elif option == '2':
            print(f'Alphabet: {fa.alphabet}')

        elif option == '3':
            print(f'Start state: {fa.start_state}')

        elif option == '4':
            print(f'Final states: {fa.final_states}')

        elif option == '5':
            print(f'Transitions: {fa.transitions}')

        elif option == '6':
            word = input('Word: ').strip()
            if fa.accepts_word(word):
                print(f'{word} is accepted by the automata.')

            else:
                print(f'{word} is not accepted by the automata.')

        elif option == '0':
            break

        else:
            print('Invalid option!')

        print()


def test_integer_finite_automata():
    integer_automata = FiniteAutomata('../integer_fa.in')

    assert integer_automata.states == ['q0', 'q1', 'q2', 'q3']
    assert integer_automata.accepts_word('123') is True
    assert integer_automata.accepts_word('0') is True
    assert integer_automata.accepts_word('-456789') is True
    assert integer_automata.accepts_word('-0') is False
    assert integer_automata.accepts_word('456789c') is False

def test_identifier_finite_automata():
    identifier_automata = FiniteAutomata('../identifier_fa.in')

    assert identifier_automata.states == ['q0', 'q1']
    assert identifier_automata.accepts_word('a123') is True
    assert identifier_automata.accepts_word('a0') is True
    assert identifier_automata.accepts_word('-456789') is False
    assert identifier_automata.accepts_word('012aads') is False
    assert identifier_automata.accepts_word('456789c') is False


if __name__ == '__main__':
    test_integer_finite_automata()
    test_identifier_finite_automata()
