class Grammar:
    def __init__(self, file_path: str):
        self.non_terminals = []
        self.terminals = []
        self.start_symbol = None
        self.productions = {}

        self.file_path = file_path
        self.__parse_file()

    def get_non_terminals(self):
        return self.non_terminals

    def get_terminals(self):
        return self.terminals

    def get_productions(self):
        return self.productions

    def get_productions_for_non_terminal(self, non_terminal):
        if non_terminal not in self.productions:
            raise Exception('Can retrieve productions for non terminal only!')

        return self.productions[non_terminal]

    def is_cfg(self):
        for key in self.productions.keys():
            if key not in self.non_terminals:
                return False

        return True

    def __parse_file(self):
        with open(self.file_path, 'r') as grammar_file:
            self.__parse_non_terminals(grammar_file.readline())
            self.__parse_terminals(grammar_file.readline())
            self.start_symbol = grammar_file.readline().strip().split('=')[1].strip()

            grammar_file.readline()  # skip line P =

            # parsing productions in form: lhs -> rhs
            for line in grammar_file.readlines():
                if not line.strip():
                    continue

                self.__parse_production(line)

    def __parse_non_terminals(self, non_terminals_line):
        fields = non_terminals_line.strip().split('=')
        self.non_terminals = fields[1].strip().split()
        self.non_terminals = list(map(lambda x: x.strip(), self.non_terminals))

    def __parse_terminals(self, terminals_line):
        fields = terminals_line.strip().split('=')
        self.terminals = fields[1].strip().split()
        self.terminals = list(map(lambda x: x.strip(), self.terminals))

    def __parse_production(self, production_line: str):
        lhs, rhs = production_line.strip().split('->')
        lhs = lhs.strip()
        rhs = list(map(lambda x: x.strip(), rhs.strip().split('|')))

        if lhs in self.productions:
            self.productions[lhs].extend(rhs)

        else:
            self.productions[lhs] = rhs

    def __str__(self):
        return (f'Grammar(non_terminals: {str(self.non_terminals)}, '
                f' terminals: {str(self.terminals)}, '
                f' start_symbol: {self.start_symbol}), '
                f'productions: {self.productions})')

    def __repr__(self):
        return str(self)
