import copy


def check_if_associative(table, n):
    for i in range(n):
        for j in range(n):
            for k in range(n):
                # (ai*aj)*ak <=> table[table[i][j]][k]
                if table[table[i][j] - 1][k] != table[i][table[j][k] - 1]:
                    return False

    return True


def check_for_0(matrix, k):
    for i in range(k):
        for j in range(k):
            if matrix[i][j] == 0:
                return True

    return False


def check_all_sub_matrix(table, k, n):
    r = len(table)
    c = len(table[0])
    t = []
    a = []
    m = []

    for i in range(0, r - k):
        for j in range(0, c - k):
            for ii in range(k):
                for jj in range(k):
                    a.append(table[i + ii][j + jj])
                t.append(a)
                a = []
            m.append(t)
            t = []

    for matrix in t:
        if check_for_0(matrix, k):
            break

        if check_if_associative(matrix, k) is False:
            return False

    return True


def print_matrix(table, n, file_name):
    file = open(file_name, 'a')
    for i in range(n):
        for j in range(n):
            # print('a' + str(table[i][j] + 1), end=' ')
            file.write('a' + str(table[i][j]) + ' ')
        file.write('\n')
        print()

    file.write('\n')


counter = 0


def backtrack(table, n, i, j, laws, file_name):
    if i == n - 1 and j == n - 1:
        for value in range(1, n + 1):
            table[i][j] = value
            if check_if_associative(table, n) is True:
                # print_matrix(table, n, file_name)

                laws.append(copy.deepcopy(table))

                global counter
                counter += 1
        return

    if j == n - 1:
        new_j = 0
        new_i = i + 1

        # if check_if_associative(table, i - 1) is False:
        #     return

    else:
        new_i = i
        new_j = j + 1

    for value in range(1, n + 1):
        table[i][j] = value

        if check_all_sub_matrix(table, n - 1, n) is False:
            continue

        backtrack(table, n, new_i, new_j, laws, file_name)


def main():
    file = open('file0.txt', 'w')
    file.write('There are no associative laws on an empty set!\n')
    file.close()

    laws = []

    for n in range(5):
        table = [[0 for x in range(n)] for y in range(n)]

        file_name = 'file' + str(n) + '.txt'

        laws = []
        global counter
        counter = 0
        backtrack(table, n, 0, 0, laws, file_name)

        file = open(file_name, 'w')
        file.write(f'The number of associative operations on a set A = {{a1, . . . , a{n}}} is {counter}!\n')

        if counter > 0:
            file.write('The laws are: \n')
        file.close()

        for law in laws:
            print_matrix(law, n, file_name)


main()
