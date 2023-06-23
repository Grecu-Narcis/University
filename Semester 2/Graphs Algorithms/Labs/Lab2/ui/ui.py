from domain.undirected_graph import *
from domain.directed_graph import *


class UI:
    def __init__(self):
        pass

    @staticmethod
    def print_menu():
        print('')
        print('Enter 1 to get the number of vertices.\n'
              'Enter 2 to print the set of vertices.\n'
              'Enter 3 to check if an edge exists.\n'
              'Enter 4 to get the in degree and out degree for a vertex.\n'
              'Enter 5 to print the set of inbound edges of a specified vertex.\n'
              'Enter 6 to print the set of outbound edges of a specified vertex.\n'
              'Enter 7 to add a vertex.\n'
              'Enter 8 to remove a vertex.\n'
              'Enter 9 to add an edge.\n'
              'Enter 10 to remove an edge.\n'
              'Enter 11 to read a undirected graph from a file - function 1.\n'
              'Enter 12 to read a undirected graph from a file - function 2.\n'
              'Enter 13 to read a directed graph from a file - function 1.\n'
              'Enter 14 to read a directed graph from a file - function 2.\n'
              'Enter 15 to save the graph to a file.\n'
              'Enter 16 to create a random graph.\n'
              'Enter 17 to print connected components.\n'
              'Enter 18 to print strongly connected components.\n'
              'Enter 19 to exit.\n')


    def main_menu(self):
        graph = read_undirected_graph_from_file_1('graph.txt')
        while True:
            self.print_menu()

            option = input('Your option is: ')

            if option == '1':
                print(f'The number of vertices in graph is: {graph.get_number_of_vertices()}')

            elif option == '2':
                vertices = [str(x) for x in graph.get_set_of_vertices()]

                if graph.get_number_of_vertices() == 0:
                    print('The graph does not contain any node.')
                    continue

                print('Vertices in the graph are: ' + ' '.join(vertices))

            elif option == '3':
                print('Enter the edge: ')
                first_node = input('First node: ')
                second_node = input('Second node: ')

                try:
                    first_node = int(first_node)
                    second_node = int(second_node)
                except ValueError:
                    print('Nodes must be integers!')
                    continue

                if graph.is_edge((first_node, second_node)):
                    print(f'Edge ({first_node}, {second_node}) exists.')

                else:
                    print(f'Edge ({first_node}, {second_node}) does not exist.')

            elif option == '4':
                vertex = input('Enter the vertex: ')

                try:
                    vertex = int(vertex)
                except ValueError:
                    print('Vertex must be an integer.')
                    continue

                try:
                    print(f'In degree: {graph.get_in_degree(vertex)}')
                    print(f'Out degree: {graph.get_out_degree(vertex)}')
                except ValueError as ve:
                    print(str(ve))

            elif option == '5':
                vertex = input('Enter the vertex: ')

                try:
                    vertex = int(vertex)
                except ValueError:
                    print('Vertex must be an integer.')
                    continue

                try:
                    edges = graph.get_in_bound_edges(vertex)

                    if len(edges) == 0:
                        print('There are no in bound edges.')
                        continue

                    str_edges = map(lambda edge: f'{edge[0], edge[1]}', edges)

                    print('Edges are: ' + ', '.join(str_edges))

                except ValueError as ve:
                    print(str(ve))

            elif option == '6':
                vertex = input('Enter the vertex: ')

                try:
                    vertex = int(vertex)
                except ValueError:
                    print('Vertex must be an integer.')
                    continue

                try:
                    edges = graph.get_out_bound_edges(vertex)

                    if len(edges) == 0:
                        print('There are no in bound edges.')
                        continue

                    str_edges = map(lambda edge: f'{edge[0], edge[1]}', edges)

                    print('Edges are: ' + ', '.join(str_edges))

                except ValueError as ve:
                    print(str(ve))

            elif option == '7':
                vertex = input('Enter vertex: ')

                try:
                    vertex = int(vertex)
                except ValueError:
                    print('vertex should be an integer.')
                    continue

                try:
                    graph.add_vertex(vertex)
                    print('Vertex added successfully!')
                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '8':
                vertex = input('Enter the vertex: ')

                try:
                    vertex = int(vertex)
                except ValueError:
                    print('Vertex must be an integer.')
                    continue

                try:
                    graph.remove_vertex(vertex)
                    print('Vertex removed successfully!')
                except ValueError as ve:
                    print(str(ve))

            elif option == '9':
                print('Enter edge: ')
                first_node = input('First node: ')
                second_node = input('Second node: ')
                cost = input('Cost: ')
                try:
                    first_node = int(first_node)
                    second_node = int(second_node)
                    cost = int(cost)
                except ValueError:
                    print('Nodes and cost must be integers.')
                    continue

                try:
                    graph.add_edge((first_node, second_node), cost)
                    print('Edge added successfully!')
                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '10':
                print('Enter edge: ')
                first_node = input('First node: ')
                second_node = input('Second node: ')

                try:
                    first_node = int(first_node)
                    second_node = int(second_node)
                except ValueError:
                    print('Nodes must be integers.')
                    continue

                try:
                    graph.remove_edge((first_node, second_node))
                    print('Edge removed successfully!')
                except ValueError as ve:
                    print(str(ve))
                    continue


            elif option == '11':
                filename = input('Enter file name: ')

                try:
                    graph = read_undirected_graph_from_file_1(filename)
                    print('Graph read successfully.')
                except IOError:
                    print('File not found.')

            elif option == '12':
                filename = input('Enter file name: ')

                try:
                    graph = read_undirected_graph_from_file_2(filename)
                    print('Graph read successfully.')
                except IOError:
                    print('File not found.')

            elif option == '13':
                filename = input('Enter file name: ')

                try:
                    graph = read_directed_graph_from_file_1(filename)
                    print('Graph read successfully.')
                except IOError:
                    print('File not found.')

            elif option == '14':
                filename = input('Enter file name: ')

                try:
                    graph = read_undirected_graph_from_file_2(filename)
                    print('Graph read successfully.')
                except IOError:
                    print('File not found.')

            elif option == '15':
                filename = input('Enter file name: ')

                if isinstance(graph, DirectedGraph):
                    write_directed_graph_to_file(filename, graph)
                else:
                    write_undirected_graph_to_file(filename, graph)
                print('Graph written successfully.')

            elif option == '16':
                number_of_vertices = input('Enter number of vertices: ')
                number_of_edges = input('Enter number of edges: ')

                try:
                    number_of_vertices = int(number_of_vertices)
                    number_of_edges = int(number_of_edges)
                except ValueError:
                    print('Number of vertices and edges must be integers.')
                    continue

                try:
                    graph = generate_random_undirected_graph(number_of_vertices, number_of_edges)
                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '17':
                connected_components = get_connected_components(graph)

                if len(connected_components) == 0:
                    print('There are no connected components.')
                    continue

                elif len(connected_components) == 1:
                    print('There is only one connected component: ')

                else:
                    print(f'There are {len(connected_components)} connected components: ')

                for component in connected_components:
                    print(component.dict_in)
                    # print(component.dict_out)

            elif option == '18':
                connected_components = get_strongly_connected_components(graph)

                if len(connected_components) == 0:
                    print('There are no strongly connected components.')
                    continue

                elif len(connected_components) == 1:
                    print('There is only one strongly connected component: ')

                else:
                    print(f'There are {len(connected_components)} strongly connected components: ')

                for component in connected_components:
                    print(component)

            elif option == '19':
                break
