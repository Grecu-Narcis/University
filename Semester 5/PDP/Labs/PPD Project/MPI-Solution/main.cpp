#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "mpi.h"

// Function to check if a color is safe for a vertex
bool is_safe(const std::vector<std::vector<int>>& graph, const std::vector<int>& colors, int vertex, int color) {
    for (int i = 0; i < graph[vertex].size(); i++) {
        if (graph[vertex][i] == 1 && colors[i] == color) {
            return false;
        }
    }
    return true;
}

// Function to perform coloring for a subset of vertices
void color_vertices(const std::vector<std::vector<int>>& graph, std::vector<int>& colors, int start, int end, int max_colors) {
    for (int vertex = start; vertex < end; vertex++) {
        for (int color = 0; color < max_colors; color++) {
            if (is_safe(graph, colors, vertex, color)) {
                colors[vertex] = color;
                break;
            }
        }
    }
}

// Main MPI Graph Coloring
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MAX_COLORS = 8;
    int n = 8;  
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 1, 0},
    };

    // Broadcast graph size and structure to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> flattened_graph;
    if (rank == 0) {
        for (const auto& row : graph) {
            flattened_graph.insert(flattened_graph.end(), row.begin(), row.end());
        }
    }

    flattened_graph.resize(n * n);
    MPI_Bcast(flattened_graph.data(), n * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Convert flattened graph back to adjacency matrix
    if (rank != 0) {
        graph.resize(n, std::vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = flattened_graph[i * n + j];
            }
        }
    }

    // Divide vertices among processes
    int chunk_size = n / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? n : start + chunk_size;

    // Initialize colors and local coloring
    std::vector<int> colors(n, -1); // colors[i] = color of node i
    color_vertices(graph, colors, start, end, MAX_COLORS);

    // Gather colors from all processes
    std::vector<int> final_colors;
    if (rank == 0) {
        final_colors.resize(n);
    }
    MPI_Gather(colors.data() + start, chunk_size, MPI_INT, final_colors.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Conflict resolution
    if (rank == 0) {
        bool conflict = true;
        while (conflict) {
            conflict = false;
            for (int u = 0; u < n; u++) {
                for (int v = u + 1; v < n; v++) {
                    if (graph[u][v] == 1 && final_colors[u] == final_colors[v]) {
                        final_colors[u] = -1;  // Mark for recoloring
                        conflict = true;
                    }
                }
            }
            for (int u = 0; u < n; u++) {
                if (final_colors[u] == -1) {
                    for (int color = 0; color < MAX_COLORS; color++) {
                        if (is_safe(graph, final_colors, u, color)) {
                            final_colors[u] = color;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Print final colors
    if (rank == 0) {
        std::cout << "Vertex Colors:\n";
        for (int i = 0; i < n; i++) {
            std::cout << "Vertex " << i << ": Color " << final_colors[i] << "\n";
        }
    }

    MPI_Finalize();
    return 0;
}
