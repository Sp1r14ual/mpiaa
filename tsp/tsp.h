#include "graph.h"

#include <vector>

/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices.

std::vector<int> tsp_greedy(const Graph& graph, int start_vertex);

std::vector<int> tsp_Bnb(const Graph& graph, int start_vertex);

std::vector<int> tsp_brute(const Graph& graph, int start_vertex);

std::vector<int> tsp(const Graph &graph, int start_vertex);