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
              'Enter 11 to get the cost of an edge.\n'
              'Enter 12 to read a graph from a file - function 1.\n'
              'Enter 13 to read a graph from a file - function 2.\n'
              'Enter 14 to save the graph to a file.\n'
              'Enter 15 to create a random graph.\n'
              'Enter 16 to get the lowest cost walk between two vertices.\n'
              'Enter 17 to find the number of distinct walks of minimum cost between the given vertices.\n'
              'Enter 18 to print the earliest and latest starting time for activities.\n'
              'Enter 19 to exit.\n')


    def main_menu(self):
        try:
            graph = read_graph_from_file_1('graph.txt')
        except FileNotFoundError:
            graph = DirectedGraph()
        except ValueError as ve:
            print(str(ve))

        while True:
            self.print_menu()

            option = input('Your option is: ')

            if option == '1':
                # print(bellman_ford(graph, 2))
                print(cycle_min_length(graph, 2))
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
                    print(f'The cost of the edge is: {graph.get_cost_of_edge((first_node, second_node))}')
                except ValueError as ve:
                    print(str(ve))
                    continue


            elif option == '12':
                filename = input('Enter file name: ')

                try:
                    graph = read_graph_from_file_1(filename)
                    print('Graph read successfully.')
                except IOError:
                    print('File not found.')
                except ValueError as ve:
                    print(str(ve))

            elif option == '13':
                filename = input('Enter file name: ')

                try:
                    graph = read_graph_from_file_2(filename)
                    print('Graph read successfully.')
                except IOError:
                    print('File not found.')
                except ValueError as ve:
                    print(str(ve))

            elif option == '14':
                filename = input('Enter file name: ')

                write_graph_to_file(filename, graph)
                print('Graph written successfully.')

            elif option == '15':
                number_of_vertices = input('Enter number of vertices: ')
                number_of_edges = input('Enter number of edges: ')

                try:
                    number_of_vertices = int(number_of_vertices)
                    number_of_edges = int(number_of_edges)
                except ValueError:
                    print('Number of vertices and edges must be integers.')
                    continue

                try:
                    graph = generate_random_graph(number_of_vertices, number_of_edges)
                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '16':
                first_node = input('Start node: ')
                second_node = input('End node: ')

                try:
                    first_node = int(first_node)
                    second_node = int(second_node)
                except ValueError:
                    print('Nodes must be integers.')
                    continue

                try:
                    cost = graph.get_path_cost(first_node, second_node)

                    if cost == infinity:
                        print('There is no path between the two nodes.')
                        continue

                    print(f'The lowest cost path is: {graph.get_path(first_node, second_node)}')
                    print(f'The cost of the path is: {graph.get_path_cost(first_node, second_node)}')
                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '17':
                first_node = input('Start node: ')
                second_node = input('End node: ')

                try:
                    first_node = int(first_node)
                    second_node = int(second_node)
                except ValueError:
                    print('Nodes must be integers.')
                    continue

                try:
                    distinct_paths = graph.min_cost_walks(first_node, second_node)
                    print(f'The number of distinct paths between {first_node} and {second_node} is: {distinct_paths}')

                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '18':
                filename = input("Enter the path to file containing the activities: ")
                graph = read_activities(filename)
                print('Activities read successfully.')

                try:
                    print('The graph is: ')
                    write_graph_to_screen(graph)

                    graph.compute_activities_times()

                    for vertex in range(1, graph.get_number_of_vertices() - 1):
                        print(f'activity: {vertex}, earliest time: {graph.earliest_start_time[vertex]}, latest time: {graph.latest_start_time[vertex]}')

                    print('Critical activities are:')
                    for vertex in range(1, graph.get_number_of_vertices() - 1):
                        if graph.earliest_start_time[vertex] == graph.latest_start_time[vertex]:
                            print(f'activity: {vertex}')

                    print(f'Minimum time of execution is: {graph.earliest_start_time[graph.get_number_of_vertices() - 1]}')

                except ValueError as ve:
                    print(str(ve))
                    continue

            elif option == '19':
                break