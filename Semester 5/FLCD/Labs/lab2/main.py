from ds.hashmap.HashMap import HashMap

if __name__ == '__main__':
    symbol_table = HashMap()

    print(symbol_table.add("a"))
    print(symbol_table.add("ana"))
    print(symbol_table.add("aan"))

    print(symbol_table.get((97, 0)))

    print(symbol_table)
