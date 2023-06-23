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


    def __str__(self):
        return ', '.join(map(lambda x: str(x), self.get_set_of_vertices()))


    def __repr__(self):
        return str(self)

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


    def get_cost(self, edge: tuple):
        if not self.is_edge(edge):
            raise ValueError('Edge does not exist!')

        return self.__costs[edge]


def make_directed_graph_from_vertex_list(graph: DirectedGraph, vertex_list: list):
    new_graph = DirectedGraph()

    for vertex in vertex_list:
        new_graph.add_vertex(vertex)

    for vertex in vertex_list:
        for successor in graph.dict_out[vertex]:
            if successor in vertex_list:
                new_graph.add_edge((vertex, successor), graph.costs[(vertex, successor)])

    return new_graph


def dfs_out(graph: DirectedGraph, vertex: int, visited_vertices: set, dfs_stack: list):
    visited_vertices.add(vertex)

    for successor in graph.dict_out[vertex]:
        if successor not in visited_vertices:
            dfs_out(graph, successor, visited_vertices, dfs_stack)

    dfs_stack.append(vertex)


def dfs_in(graph: DirectedGraph, vertex: int, visited_vertices: set):
    connected_component = []

    nodes_stack = [vertex]

    while len(nodes_stack) > 0:
        current_node = nodes_stack.pop()

        if current_node in visited_vertices:
            continue

        visited_vertices.add(current_node)

        connected_component.append(current_node)

        for predecessor in graph.dict_in[current_node]:
            nodes_stack.append(predecessor)

    return connected_component


def get_strongly_connected_components(graph):
    visited_vertices = set()
    number_of_connected_components = 0

    nodes_stack = []

    for vertex in graph.get_set_of_vertices():
        if vertex in visited_vertices:
            continue

        dfs_out(graph, vertex, visited_vertices, nodes_stack)

        # a new connected component was found
        # we need to visit every node we can reach from this vertex

    visited_vertices.clear()
    connected_components = {}

    while len(nodes_stack) > 0:
        current_vertex = nodes_stack.pop()

        if current_vertex in visited_vertices:
            continue

        number_of_connected_components += 1
        connected_components[number_of_connected_components] = dfs_in(graph, current_vertex, visited_vertices)

    strongly_components = []

    for component in connected_components.values():
        strongly_components.append(make_directed_graph_from_vertex_list(graph, component))

    return strongly_components


def read_directed_graph_from_file_1(filename: str):
    file = open(filename, 'rt')

    number_of_vertices, number_of_edges = [int(x) for x in file.readline().strip().split()]

    graph = DirectedGraph(number_of_vertices)

    for i in range(number_of_edges):
        x, y, cost = map(int, file.readline().strip().split())

        graph.add_edge((x, y), cost)

    file.close()

    return graph


def read_directed_graph_from_file_2(filename: str):
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


def write_directed_graph_to_file(filename: str, graph: DirectedGraph):
    file = open(filename, 'wt')

    for node in graph.get_set_of_vertices():
        if len(graph.dict_in[node]) == 0 and len(graph.dict_out[node]) == 0:
            file.write(str(node) + '\n')

        else:
            for successor in graph.dict_out[node]:
                file.write(f'{node} {successor} {graph.costs[(node, successor)]}\n')

    file.close()


def generate_random_directed_graph(number_of_vertices: int, number_of_edges: int):
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
