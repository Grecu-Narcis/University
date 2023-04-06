from random import randint


class DirectedGraph:
    def __init__(self, number_of_vertices=0):
        self.__dict_in = {}
        self.__dict_out = {}
        self.__costs = {}

        for i in range(number_of_vertices):
            self.__dict_in[i] = []
            self.__dict_out[i] = []


    @property
    def dict_in(self):
        return self.__dict_in


    @property
    def dict_out(self):
        return self.__dict_out

    @property
    def costs(self):
        return self.__costs


    def is_vertex(self, vertex_to_check: int):
        if vertex_to_check not in self.__dict_in:
            return False

        return True


    def add_vertex(self, vertex_to_add: int):
        if self.is_vertex(vertex_to_add):
            raise ValueError('Vertex already in graph!')

        self.__dict_in[vertex_to_add] = []
        self.__dict_out[vertex_to_add] = []


    def remove_vertex(self, vertex_to_remove: int):
        if not self.is_vertex(vertex_to_remove):
            raise ValueError('Vertex does not exist!')

        # in_edges = self.get_in_bound_edges(vertex_to_remove)
        # out_edges = self.get_out_bound_edges(vertex_to_remove)
        #
        # for edge in in_edges:
        #     del self.__costs[edge]
        #
        # for edge in out_edges:
        #     del self.__costs[edge]

        for vertex in self.__dict_out[vertex_to_remove]:
            del self.__costs[(vertex_to_remove, vertex)]
            
            self.__dict_in[vertex].remove(vertex_to_remove)

        for vertex in self.__dict_in[vertex_to_remove]:
            del self.__costs[(vertex, vertex_to_remove)]

            self.__dict_out[vertex].remove(vertex_to_remove)

        del self.__dict_in[vertex_to_remove]
        del self.dict_out[vertex_to_remove]

    def is_edge(self, edge_to_check: tuple):
        start_point = edge_to_check[0]
        end_point = edge_to_check[1]

        if not self.is_vertex(start_point) or not self.is_vertex(end_point):
            return False

        # (x, y) should check if y is successor of x and x predecessor of y

        if start_point not in self.__dict_in[end_point]:
            return False

        if end_point not in self.__dict_out[start_point]:
            return False

        return True


    def add_edge(self, edge_to_add: tuple, cost: int):
        start_point = edge_to_add[0]
        end_point = edge_to_add[1]

        if self.is_edge(edge_to_add):
            raise ValueError('Edge is already in graph!')

        if not self.is_vertex(start_point) or not self.is_vertex(end_point):
            raise ValueError('Vertices are not in graph!')

        self.__dict_out[start_point].append(end_point)
        self.__dict_in[end_point].append(start_point)
        self.__costs[edge_to_add] = cost


    def remove_edge(self, edge_to_remove: tuple):
        if not self.is_edge(edge_to_remove):
            raise ValueError('Edge does not exist!')

        # (x, y) -> remove y from Dout x
        # (x, y) -> remove x from Din y
        x, y = edge_to_remove

        self.__dict_in[y].remove(x)
        self.__dict_out[x].remove(y)
        del self.__costs[edge_to_remove]


    def get_number_of_vertices(self):
        return len(self.__dict_in)


    def get_set_of_vertices(self):
        return list(self.__dict_in.keys())


    def get_in_degree(self, vertex: int):
        if not self.is_vertex(vertex):
            raise ValueError('Vertex not in graph!')

        return len(self.__dict_in[vertex])


    def get_out_degree(self, vertex: int):
        if not self.is_vertex(vertex):
            raise ValueError('Vertex not in graph!')

        return len(self.__dict_out[vertex])


    def get_in_bound_edges(self, vertex: int):
        if not self.is_vertex(vertex):
            raise ValueError('Vertex not in graph.')

        edges = []

        for in_vertex in self.__dict_in[vertex]:
            edges.append((in_vertex, vertex))

        return edges


    def get_out_bound_edges(self, vertex: int):
        if not self.is_vertex(vertex):
            raise ValueError('Vertex not in graph.')

        edges = []

        for out_vertex in self.__dict_out[vertex]:
            edges.append((vertex, out_vertex))

        return edges


    def get_all_edges(self):
        edges = []

        for vertex in self.get_set_of_vertices():
            for edge in self.get_out_bound_edges(vertex):
                edges.append((edge, self.__costs[edge]))

        return edges


    def make_copy(self):
        copy_graph = DirectedGraph()

        for vertex in self.get_set_of_vertices():
            copy_graph.add_vertex(vertex)

        for vertex in self.get_set_of_vertices():
            for edge in self.get_in_bound_edges(vertex):
                copy_graph.add_edge(edge, self.costs[edge])

        return copy_graph


def read_graph_from_file_1(filename: str):
    file = open(filename, 'rt')

    number_of_vertices, number_of_edges = [int(x) for x in file.readline().strip().split()]

    graph = DirectedGraph(number_of_vertices)

    for i in range(number_of_edges):
        x, y, cost = map(int, file.readline().strip().split())

        graph.add_edge((x, y), cost)

    file.close()

    return graph


def read_graph_from_file_2(filename: str):
    file = open(filename, 'rt')

    graph = DirectedGraph()

    for line in file.readlines():
        split_line = line.strip().split()

        if len(split_line) == 1:
            graph.add_vertex(int(split_line[0]))

        else:
            x, y, cost = map(int, line.strip().split())

            if not graph.is_vertex(x):
                graph.add_vertex(x)

            if not graph.is_vertex(y):
                graph.add_vertex(y)

            graph.add_edge((x, y), cost)

    return graph


def write_graph_to_file(filename: str, graph: DirectedGraph):
    file = open(filename, 'wt')

    for node in graph.get_set_of_vertices():
        if len(graph.dict_in[node]) == 0 and len(graph.dict_out[node]) == 0:
            file.write(str(node) + '\n')

        else:
            for successor in graph.dict_out[node]:
                file.write(f'{node} {successor} {graph.costs[(node, successor)]}\n')

    file.close()


def generate_random_graph(number_of_vertices: int, number_of_edges: int):
    if number_of_vertices * number_of_vertices < number_of_edges:
        raise ValueError(f"With {number_of_vertices} vertices you can have at most {number_of_vertices ** 2} edges!")

    graph = DirectedGraph(number_of_vertices)

    while number_of_edges != 0:
        x = randint(0, number_of_vertices - 1)
        y = randint(0, number_of_vertices - 1)
        cost = randint(-10, 10)

        try:
            graph.add_edge((x, y), cost)
            number_of_edges -= 1
        except ValueError:
            continue
    return graph
