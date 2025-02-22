class Transition:
    def __init__(self, transition_as_string: str):
        transition_fields = transition_as_string[1:-1].split(',')

        self.source = transition_fields[0].strip()
        self.destination = transition_fields[1].strip()
        self.label = transition_fields[2].strip()

    def __str__(self):
        return f'Transition({self.source} -> {self.destination} via {self.label})'

    def __repr__(self):
        return str(self)
