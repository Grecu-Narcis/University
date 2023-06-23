#include <iostream>
#include "DirectedGraph.h"

class UI {
public:
    UI() {}

    static void print_menu() {
        std::cout << std::endl;
        std::cout << "\nEnter 1 to get the number of vertices.\n"
            << "Enter 2 to print the set of vertices.\n"
            << "Enter 3 to check if an edge exists.\n"
            << "Enter 4 to get the in degree and out degree for a vertex.\n"
            << "Enter 5 to print the set of inbound edges of a specified vertex.\n"
            << "Enter 6 to print the set of outbound edges of a specified vertex.\n"
            << "Enter 7 to add a vertex.\n"
            << "Enter 8 to remove a vertex.\n"
            << "Enter 9 to add an edge.\n"
            << "Enter 10 to remove an edge.\n"
            << "Enter 11 to read a graph from a file - function 1.\n"
            << "Enter 12 to read a graph from a file - function 2.\n"
            << "Enter 13 to save the graph to a file.\n"
            << "Enter 14 to create a random graph.\n"
            << "Enter 15 to exit.\n";
    }

    void main_menu() {
        DirectedGraph graph = read_graph_from_file_1("graph.txt");

        while (true) {
            print_menu();

            string option;
            cout << "Your option is: ";
            cin >> option;

            if (option == "1") {
                cout << "The number of vertices in graph is: " << graph.get_number_of_vertices() << endl;
            }
            else if (option == "2") {
                vector<int> vertices = graph.get_set_of_vertices();
                if (graph.get_number_of_vertices() == 0) {
                    cout << "The graph does not contain any node." << endl;
                    continue;
                }
                cout << "Vertices in the graph are: ";
                for (int i = 0; i < vertices.size(); i++) {
                    cout << vertices[i] << " ";
                }
                cout << endl;
            }
            else if (option == "3") {
                int first_node, second_node;
                cout << "Enter the edge: " << endl;
                cout << "First node: ";
                cin >> first_node;
                cout << "Second node: ";
                cin >> second_node;

                if (graph.is_edge(make_pair(first_node, second_node))) {
                    cout << "Edge (" << first_node << ", " << second_node << ") exists." << endl;
                }
                else {
                    cout << "Edge (" << first_node << ", " << second_node << ") does not exist." << endl;
                }
            }

            else if (option == "4") {
                std::cout << "Enter the vertex: ";
                std::string vertex;
                std::cin >> vertex;

                try {
                    int vertex_int = std::stoi(vertex);

                    try {
                        std::cout << "In degree: " << graph.get_in_degree(vertex_int) << std::endl;
                        std::cout << "Out degree: " << graph.get_out_degree(vertex_int) << std::endl;
                    }
                    catch (std::exception& ve) {
                        std::cout << ve.what() << std::endl;
                    }
                }
                catch (std::exception& e) {
                    std::cout << "Vertex must be an integer." << std::endl;
                    continue;
                }
            }
            else if (option == "5") {
                std::cout << "Enter the vertex: ";
                std::string vertex;
                std::cin >> vertex;

                try {
                    int vertex_int = std::stoi(vertex);

                    try {
                        std::vector<std::pair<int, int>> edges = graph.get_in_bound_edges(vertex_int);

                        if (edges.size() == 0) {
                            std::cout << "There are no in bound edges." << std::endl;
                            continue;
                        }

                        std::vector<std::string> str_edges;
                        for (auto edge : edges) {
                            str_edges.push_back("{" + std::to_string(edge.first) + ", " + std::to_string(edge.second) + "}");
                        }

                        std::cout << "Edges are: ";
                        for (auto edge : str_edges)
                            std::cout << edge << " ";
                    }

                    catch (std::exception& ve) {
                        std::cout << ve.what() << std::endl;
                    }
                }
                catch (std::exception& e) {
                    std::cout << e.what() << endl;
                }
            }

            else if (option == "6") {
                std::cout << "Enter the vertex: ";
                std::string vertex;
                std::cin >> vertex;

                try {
                    int vertex_int = std::stoi(vertex);

                    try {
                        std::vector<std::pair<int, int>> edges = graph.get_out_bound_edges(vertex_int);

                        if (edges.size() == 0) {
                            std::cout << "There are no in bound edges." << std::endl;
                            continue;
                        }

                        std::vector<std::string> str_edges;
                        for (auto edge : edges) {
                            str_edges.push_back("{" + std::to_string(edge.first) + ", " + std::to_string(edge.second) + "}");
                        }

                        std::cout << "Edges are: ";
                        for (auto edge : str_edges)
                            std::cout << edge << " ";
                    }
                    catch (std::exception& ve) {
                        std::cout << ve.what() << std::endl;
                    }
                }
                catch (std::exception& e) {
                    std::cout << "Vertex must be an integer." << std::endl;
                    continue;
                }
            }

            else if (option == "7") {
                string vertex;
                cout << "Enter vertex: ";
                cin >> vertex;

                try {
                    int vertex_int = stoi(vertex);
                    graph.add_vertex(vertex_int);
                    cout << "Vertex added successfully!" << endl;
                }
                catch (const std::invalid_argument& ia) {
                    cout << "Vertex should be an integer." << endl;
                    continue;
                }
                catch (const std::exception& e) {
                    cout << e.what() << endl;
                    continue;
                }
            }


            else if (option == "8") {
                string vertex;
                cout << "Enter the vertex: ";
                cin >> vertex;

                try {
                    int vertex_int = stoi(vertex);
                    graph.remove_vertex(vertex_int);
                    cout << "Vertex removed successfully!" << endl;
                }
                catch (const std::invalid_argument& ia) {
                    cout << "Vertex must be an integer." << endl;
                    continue;
                }
                catch (const std::exception& e) {
                    cout << e.what() << endl;
                    continue;
                }
            }

            else if (option == "9") {
                std::cout << "Enter edge: " << std::endl;
                std::cout << "First node: ";
                std::string first_node;
                std::cin >> first_node;
                std::cout << "Second node: ";
                std::string second_node;
                std::cin >> second_node;
                std::cout << "Cost: ";
                std::string cost;
                std::cin >> cost;
                try {
                    int first_node_int = std::stoi(first_node);
                    int second_node_int = std::stoi(second_node);
                    int cost_int = std::stoi(cost);
                    try {
                        graph.add_edge(std::make_pair(first_node_int, second_node_int), cost_int);
                        std::cout << "Edge added successfully!" << std::endl;
                    }
                    catch (std::exception& ve) {
                        std::cout << ve.what() << std::endl;
                        continue;
                    }
                }
                catch (std::exception& e) {
                    std::cout << "Nodes and cost must be integers." << std::endl;
                    continue;
                }
            }


            else if (option == "10") {
                std::cout << "Enter edge: " << std::endl;
                std::cout << "First node: ";
                std::string first_node;
                std::cin >> first_node;
                std::cout << "Second node: ";
                std::string second_node;
                std::cin >> second_node;

                int first_node_int;
                int second_node_int;

                try {
                    first_node_int = std::stoi(first_node);
                    second_node_int = std::stoi(second_node);
                }

                catch (std::invalid_argument) {
                    std::cout << "Nodes must be integers." << std::endl;
                    continue;
                }

                try {
                    graph.remove_edge(std::make_pair(first_node_int, second_node_int));
                    std::cout << "Edge removed successfully!" << std::endl;
                }
                catch (std::exception& ve) {
                    std::cout << ve.what() << std::endl;
                    continue;
                }
            }

            else if (option == "11") {
                string filename;
                cout << "Enter file name: ";
                cin >> filename;

                try {
                    graph = read_graph_from_file_1(filename);
                    cout << "Graph read successfully." << endl;
                }
                catch (const std::exception& e) {
                    cout << "File not found." << endl;
                }
            }

            else if (option == "12") {
                string filename;
                cout << "Enter file name: ";
                cin >> filename;

                try {
                    graph = read_graph_from_file_2(filename);
                    cout << "Graph read successfully." << endl;
                }
                catch (const std::exception& e) {
                    cout << "File not found." << endl;
                }
            }

            else if (option == "13") {
                string filename;
                cout << "Enter file name: ";
                cin >> filename;

                write_graph_to_file(filename, graph);
                cout << "Graph written successfully." << endl;
            }

            else if (option == "14") {
                int number_of_vertices, number_of_edges;

                string vertices, edges;

                std::cout << "Enter number of vertices: ";
                std::cin >> vertices;
                std::cout << "Enter number of edges: ";
                std::cin >> edges;


                try {
                    number_of_vertices = std::stoi(vertices);
                    number_of_edges = std::stoi(edges);
                }

                catch (std::invalid_argument) {
                    std::cout << "Number of vertices and edges must be integers." << std::endl;
                    continue;
                }

                try {
                    graph = generate_random_graph(number_of_vertices, number_of_edges);
                }

                catch (std::exception& ve) {
                    std::cout << ve.what() << std::endl;
                    continue;
                }
            }

            else if (option == "15")
                break;
        }
    }
};