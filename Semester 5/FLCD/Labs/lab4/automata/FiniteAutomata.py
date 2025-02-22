from automata.Transition import Transition


class FiniteAutomata:
    def __init__(self, filename: str):
        with open(filename, 'r') as input_file:
            for line in input_file.readlines():
                line = line.strip()

                if line == '':
                    continue

                identifier, values = line.split('=')

                if identifier == 'states':
                    self.states = FiniteAutomata.__split_values(values)

                elif identifier == 'alphabet':
                    self.alphabet = FiniteAutomata.__split_values(values)

                elif identifier == 'start':
                    self.start_state = values

                elif identifier == 'final':
                    self.final_states = FiniteAutomata.__split_values(values)

                elif identifier == 'transitions':
                    self.transitions = list(map(lambda x: Transition(x), FiniteAutomata.__split_values(values)))

    @staticmethod
    def __split_values(initial_values: str) -> list[str]:
        values = initial_values.strip().split(';')
        return list(map(lambda x: x.strip(), values))

    def accepts_word(self, word: str):
        current_state = self.start_state

        for ch in word:
            found = False

            for transition in self.transitions:
                if transition.source == current_state and transition.label == ch:
                    current_state = transition.destination
                    found = True
                    break

            if not found:
                return False

        return current_state in self.final_states

    def __str__(self):
        result = ''
        result += f'states: {self.states}\n'
        result += f'alphabet: {self.alphabet}\n'
        result += f'start: {self.start_state}\n'
        result += f'final: {self.final_states}\n'
        result += f'transitions: {self.transitions}\n'

        return result
