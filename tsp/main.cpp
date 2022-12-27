#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

#include "tsp.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);

    //полный граф
    std::vector<int> counts = {5, 6, 7, 8, 9, 10};
    for (int N : counts)
    {
        srand(time(NULL));
        Graph graph;
        std::default_random_engine generator;
        //количество вершин
        std::uniform_int_distribution<int> distributionEdge(1, 100);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto t2 = std::chrono::high_resolution_clock::now();
        double timee;

        std::vector<int> vertices(N);
        for (int i = 0; i < N; i++) graph.add_vertex(i); //создаём N вершин
        for (int i = 0; i < N-1; i++)
            for (int j = i+1; j < N; j++) 
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
        
        std::cout << "N = " << N << std::endl;
        t1 = std::chrono::high_resolution_clock::now();
        tsp_brute(graph, start);
        t2 = std::chrono::high_resolution_clock::now();
        timee = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "Bruteforce" << std::endl;
        std::cout << "time: " << timee << " sec." << std::endl;
        std::cout << "--------------------------------------" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();
        tsp_Bnb(graph, start);
        t2 = std::chrono::high_resolution_clock::now();
        timee = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "Branch and bound" << std::endl; 
        std::cout << "time: " << timee << " sec." << std::endl;
        std::cout << "--------------------------------------" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();
        tsp_greedy(graph, start);
        t2 = std::chrono::high_resolution_clock::now();
        timee = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "Greedy" << std::endl;
        std::cout << "time: " << timee << " sec." << std::endl;
        std::cout << "--------------------------------------" << std::endl;
    }
    return result;
}
