#ifndef __DIRECTED_GRAPH_CPP__
#define __DIRECTED_GRAPH_CPP__

#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

class DirectedGraph
{
public:
    std::map<int, std::vector<int>> dict_in;
    std::map<int, std::vector<int>> dict_out;
    std::map<std::pair<int, int>, int> costs;

public:
    DirectedGraph(int number_of_vertices = 0)
    {
        for (int i = 0; i < number_of_vertices; i++)
        {
            dict_in[i] = {};
            dict_out[i] = {};
        }
    }

    bool is_vertex(int vertex_to_check)
    {
        if (dict_in.find(vertex_to_check) == dict_in.end())
            return false;
        return true;
    }

    void add_vertex(int vertex_to_add)
    {
        if (is_vertex(vertex_to_add))
            throw std::exception("Vertex already in graph!");
        dict_in[vertex_to_add] = {};
        dict_out[vertex_to_add] = {};
    }

    void remove_vertex(int vertex_to_remove)
    {
        if (!is_vertex(vertex_to_remove))
            throw std::runtime_error("Vertex does not exist!");
        std::vector<std::pair<int, int>> in_edges = get_in_bound_edges(vertex_to_remove);
        std::vector<std::pair<int, int>> out_edges = get_out_bound_edges(vertex_to_remove);

        for (auto edge : in_edges)
            costs.erase(edge);

        for (auto edge : out_edges)
            costs.erase(edge);

        for (auto vertex : dict_out[vertex_to_remove])
        {
            auto newEnd = remove(dict_in[vertex].begin(), dict_in[vertex].end(), vertex_to_remove);

            dict_in[vertex].erase(newEnd, dict_in[vertex].end());
        }

        for (auto vertex : dict_in[vertex_to_remove])
        {
            auto newEnd = remove(dict_out[vertex].begin(), dict_out[vertex].end(), vertex_to_remove);

            dict_out[vertex].erase(newEnd, dict_out[vertex].end());
        }

        dict_in.erase(vertex_to_remove);
        dict_out.erase(vertex_to_remove);
    }

    bool is_edge(std::pair<int, int> edge_to_check) {
        int start_point = std::get<0>(edge_to_check);
        int end_point = std::get<1>(edge_to_check);

        if (!is_vertex(start_point) || !is_vertex(end_point)) {
            return false;
        }

        // (x, y) should check if y is successor of x and x predecessor of y

        if (find(dict_in[end_point].begin(), dict_in[end_point].end(), start_point) == dict_in[end_point].end()) {
            return false;
        }

        if (dict_out.find(start_point) == dict_out.end() ||
            find(dict_out[start_point].begin(), dict_out[end_point].end(), end_point) == dict_out[start_point].end()) {
            return false;
        }

        return true;
    }

    void add_edge(std::pair<int, int> edge_to_add, int cost) {
        int start_point = std::get<0>(edge_to_add);
        int end_point = std::get<1>(edge_to_add);

        if (is_edge(edge_to_add)) {
            throw std::exception("Edge is already in graph!");
        }

        if (!is_vertex(start_point) || !is_vertex(end_point)) {
            throw std::exception("Vertices are not in graph!");
        }

        dict_out[start_point].push_back(end_point);
        dict_in[end_point].push_back(start_point);
        costs[edge_to_add] = cost;
    }

    void remove_edge(std::pair<int, int> edge_to_remove) {
        if (!is_edge(edge_to_remove)) {
            throw std::exception("Edge does not exist!");
        }

        // (x, y) -> remove y from Dout x
        // (x, y) -> remove x from Din y
        int x, y;
        x = edge_to_remove.first;
        y = edge_to_remove.second;

        remove(dict_in[y].begin(), dict_in[y].end(), x);
        remove(dict_out[x].begin(), dict_out[x].end(), y);

        costs.erase(edge_to_remove);
    }

    int get_number_of_vertices()
    {
        return this->dict_in.size();
    }

    std::vector<int> get_set_of_vertices() {
        std::vector<int> vertices;
        for (auto const& x : dict_in) {
            vertices.push_back(x.first);
        }
        return vertices;
    }

    int get_in_degree(int vertex) {
        if (!is_vertex(vertex)) {
            throw std::invalid_argument("Vertex not in graph!");
        }
        return dict_in[vertex].size();
    }

    int get_out_degree(int vertex) {
        if (!is_vertex(vertex)) {
            throw std::invalid_argument("Vertex not in graph!");
        }

        return dict_out[vertex].size();
    }

    vector<pair<int, int>> get_in_bound_edges(int vertex) {
        if (!is_vertex(vertex)) {
            throw std::invalid_argument("Vertex not in graph.");
        }

        vector<pair<int, int>> edges;

        for (auto in_vertex : dict_in[vertex]) {
            edges.emplace_back(in_vertex, vertex);
        }

        return edges;
    }

    vector<pair<int, int>> get_out_bound_edges(int vertex) {
        if (!is_vertex(vertex)) {
            throw std::invalid_argument("Vertex not in graph.");
        }

        vector<pair<int, int>> edges;

        for (auto out_vertex : dict_out[vertex]) {
            edges.emplace_back(vertex, out_vertex);
        }

        return edges;
    }


    vector<pair<pair<int, int>, int>> get_all_edges() {
        vector<pair<pair<int, int>, int>> edges;

        for (auto vertex : get_set_of_vertices()) {
            for (auto edge : get_out_bound_edges(vertex)) {
                edges.push_back(make_pair(edge, costs[edge]));
            }
        }

        return edges;
    }

    DirectedGraph make_copy() {
        DirectedGraph copy_graph;

        for (auto vertex : get_set_of_vertices()) {
            copy_graph.add_vertex(vertex);
        }

        for (auto vertex : get_set_of_vertices()) {
            for (auto edge : get_in_bound_edges(vertex)) {
                copy_graph.add_edge(edge, costs[edge]);
            }
        }

        return copy_graph;
    }

};

DirectedGraph read_graph_from_file_1(string filename) {
    ifstream file(filename);

    int number_of_vertices, number_of_edges;
    file >> number_of_vertices >> number_of_edges;

    DirectedGraph graph(number_of_vertices);

    for (int i = 0; i < number_of_edges; i++) {
        int x, y, cost;
        file >> x >> y >> cost;

        graph.add_edge(make_pair(x, y), cost);
    }

    file.close();

    return graph;
}

DirectedGraph read_graph_from_file_2(string filename) {
    ifstream file(filename);

    DirectedGraph graph;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> split_line{ istream_iterator<string>{iss}, istream_iterator<string>{} };

        if (split_line.size() == 1) {
            graph.add_vertex(stoi(split_line[0]));
        }
        else {
            int x, y, cost;
            x = stoi(split_line[0]);
            y = stoi(split_line[1]);
            cost = stoi(split_line[2]);

            if (!graph.is_vertex(x)) {
                graph.add_vertex(x);
            }

            if (!graph.is_vertex(y)) {
                graph.add_vertex(y);
            }

            graph.add_edge(make_pair(x, y), cost);
        }
    }

    return graph;
}

void write_graph_to_file(string filename, DirectedGraph graph) {
    ofstream file;
    file.open(filename);

    for (int node : graph.get_set_of_vertices()) {
        if (graph.dict_in[node].size() == 0 && graph.dict_out[node].size() == 0) {
            file << node << endl;
        }
        else {
            for (int successor : graph.dict_out[node]) {
                file << node << " " << successor << " " << graph.costs[make_pair(node, successor)] << endl;
            }
        }
    }
    file.close();
}

DirectedGraph generate_random_graph(int number_of_vertices, int number_of_edges) {
    if (number_of_vertices * number_of_vertices < number_of_edges) {
        string message = string("With ") + to_string(number_of_vertices) + " vertices you can have at most " + to_string(number_of_vertices * 2) + string(" edges!");
        throw std::exception(message.c_str());
    }

    DirectedGraph graph(number_of_vertices);

    while (number_of_edges != 0) {
        int x = rand() % (number_of_vertices - 1);
        int y = rand() % (number_of_vertices - 1);
        int cost = rand() % 20 - 10;

        try {
            graph.add_edge(make_pair(x, y), cost);
            number_of_edges -= 1;
        }
        catch (std::exception& e) {
            continue;
        }
    }

    return graph;
}

#endif