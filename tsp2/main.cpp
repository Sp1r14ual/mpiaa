#define CATCH_CONFIG_RUNNER

#include "random"
#include "../catch.hpp"
#include <chrono>
#include <random>
#include "tsp.h"

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);

    std::vector<int> counts = {5, 6, 7, 8, 9, 10};

    for (int N : counts)
    {
        srand(time(NULL));
        Graph graph;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distributionEdge(1, 100);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto t2 = std::chrono::high_resolution_clock::now();
        double timee;



        std::vector<int> vertices(N);
        for (int i = 0; i < N; i++) 
            graph.add_vertex(i);
        for (int i = 0; i < N - 1; i++)
            for (int j = i + 1; j < N; j++)
                graph.add_edge(i, j, distributionEdge(generator));

        int start = 0;

        for (int i = 0; i < N; i++)
        {
            printf("%d: ", i);
            std::vector<int> adj = graph.get_adjacent_vertices(i);
            for (int j = 0; j < adj.size(); j++)
                printf("%d(%f) ", adj[j], graph.edge_weight(i, adj[j]));
            printf("\n");
        }

        t1 = std::chrono::high_resolution_clock::now();
        tsp(graph, start);
        t2 = std::chrono::high_resolution_clock::now();
        timee = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "N = " << N << std::endl;
        printf("%f\n", timee);

    }

    return result;

}