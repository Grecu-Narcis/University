from random import randint

from domain.directed_graph import DirectedGraph


class UndirectedGraph(DirectedGraph):
    def __init__(self, number_of_vertices=0):
        super().__init__(number_of_vertices)

    @property
    def dict_in(self):
        return super().dict_in

    @property
    def dict_out(self):
        return super().dict_out

    @property
    def costs(self):
        return super().costs


    def add_edge(self, edge_to_add: tuple, cost: int):
        try:
            super().add_edge(edge_to_add, cost)
            super().add_edge((edge_to_add[1], edge_to_add[0]), cost)
        except ValueError:
            pass

    def remove_edge(self, edge_to_remove: tuple):
        super().remove_edge(edge_to_remove)
        super().remove_edge((edge_to_remove[1], edge_to_remove[0]))

    def get_cost(self, edge_to_check: tuple):
        return super().get_cost(edge_to_check)


    def get_degree(self, vertex_to_check: int):
        return len(self.dict_in[vertex_to_check]) + len(self.dict_out[vertex_to_check])

    def get_in_degree(self, vertex_to_check: int):
        return len(self.dict_in[vertex_to_check])

    def get_out_degree(self, vertex_to_check: int):
        return len(self.dict_out[vertex_to_check])

    def get_number_of_edges(self):
        return len(self.costs) // 2

    def get_number_of_vertices(self):
        return len(self.dict_in)


    def get_all_edges(self):
        return super().get_all_edges()

    def get_in_bound_edges(self, vertex_to_check: int):
        return super().get_in_bound_edges(vertex_to_check)


    def get_out_bound_edges(self, vertex_to_check: int):
        return super().get_out_bound_edges(vertex_to_check)


    def get_set_of_vertices(self):
        return super().get_set_of_vertices()


    def __str__(self):
        return ', '.join(map(lambda x: str(x), self.get_set_of_vertices()))


    def __repr__(self):
        return str(self)


def read_undirected_graph_from_file_1(filename: str):
    file = open(filename, 'rt')

    number_of_vertices, number_of_edges = [int(x) for x in file.readline().strip().split()]

    graph = UndirectedGraph(number_of_vertices)

    for i in range(number_of_edges):
        x, y, cost = map(int, file.readline().strip().split())

        graph.add_edge((x, y), cost)

    file.close()

    return graph


def read_undirected_graph_from_file_2(filename: str):
    file = open(filename, 'rt')

    graph = UndirectedGraph()

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


def write_undirected_graph_to_file(filename: str, graph: DirectedGraph):
    file = open(filename, 'wt')

    edges_written = set()

    for node in graph.get_set_of_vertices():
        if len(graph.dict_in[node]) == 0 and len(graph.dict_out[node]) == 0:
            file.write(str(node) + '\n')

        else:
            for successor in graph.dict_out[node]:
                if (node, successor) in edges_written:
                    continue

                edges_written.add((node, successor))
                edges_written.add((successor, node))

                file.write(f'{node} {successor} {graph.costs[(node, successor)]}\n')

    file.close()


def make_undirected_graph_from_vertex_list(graph: UndirectedGraph, vertex_list: list):
    new_graph = UndirectedGraph()

    for vertex in vertex_list:
        new_graph.add_vertex(vertex)

    for vertex in vertex_list:
        for successor in graph.dict_out[vertex]:
            if successor in vertex_list:
                new_graph.add_edge((vertex, successor), graph.costs[(vertex, successor)])

    return new_graph


def generate_random_undirected_graph(number_of_vertices: int, number_of_edges: int):
    if number_of_vertices * number_of_vertices < number_of_edges:
        raise ValueError(f"With {number_of_vertices} vertices you can have at most {number_of_vertices ** 2} edges!")

    graph = UndirectedGraph(number_of_vertices)

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


def dfs(graph, vertex, visited_vertices):
    connected_component = []
    nodes_stack = [vertex]

    while len(nodes_stack) > 0:
        current_node = nodes_stack.pop()

        if current_node in visited_vertices:
            continue

        visited_vertices.add(current_node)

        connected_component.append(current_node)

        for successor in graph.dict_out[current_node]:
            nodes_stack.append(successor)

    return connected_component


def get_connected_components(graph):
    visited_vertices = set()
    number_of_connected_components = 0

    connected_components = {}  #

    for vertex in graph.get_set_of_vertices():
        if vertex in visited_vertices:
            continue

        # a new connected component was found
        # we need to visit every node we can reach from this vertex

        number_of_connected_components += 1
        connected_components[number_of_connected_components] = dfs(graph, vertex, visited_vertices)

    graph_components = []

    for component in connected_components.values():
        # print(component)
        graph_components.append(make_undirected_graph_from_vertex_list(graph, component))

    return graph_components





# nodes_stack = [vertex]
        #
        # while len(nodes_stack) > 0:
        #     current_node = nodes_stack.pop()
        #
        #     if current_node in visited_vertices:
        #         continue
        #
        #     visited_vertices.add(current_node)
        #
        #     connected_components[number_of_connected_components].append(current_node)
        #
        #     for successor in graph.dict_out[current_node]:
        #         nodes_stack.append(successor)