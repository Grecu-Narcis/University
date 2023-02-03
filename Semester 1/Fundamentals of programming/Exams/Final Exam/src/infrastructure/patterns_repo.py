import copy


class PatternRepo:
    def __init__(self, file_name='patterns.txt'):
        self.__patterns = {}
        self.__file_name = file_name

    def find_pattern(self, pattern_name):
        if pattern_name in self.__patterns:
            return self.__patterns[pattern_name]

        return None


    def load_file(self):
        try:
            file = open(self.__file_name, 'rt')
        except IOError:
            return

        for line in file.readlines():
            if line.strip() == '':
                continue
            pattern_args = line.strip().split()
            pattern_name = pattern_args[0]
            pattern_size = int(pattern_args[1])
            pattern = pattern_args[2]

            pattern_matrix = []
            elements = pattern.strip().split(',')
            for i in range(pattern_size):
                pattern_matrix.append(copy.deepcopy(elements[i*pattern_size:(i+1)*pattern_size]))

            self.__patterns[pattern_name] = pattern_matrix

        file.close()

    def get_all(self):
        return self.__patterns
