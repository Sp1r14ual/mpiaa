#include "tsp.h"
#include <algorithm>
//#include <numeric>
#include <limits>
#include <stdio.h>
#include <iostream>
using namespace std;


double Length(const Graph& graph, vector<int> Path)
{
    double len = 0;
    for (int i = 0; i < Path.size() - 1; i++)
    {
        if (!graph.has_edge(Path[i], Path[i + 1])) 
            return numeric_limits<double>::infinity();
        len += graph.edge_weight(Path[i], Path[i + 1]);
    }
    len += graph.edge_weight(Path[Path.size() - 1], Path[0]);
    return len;
}

vector<int> tsp_greedy(const Graph& graph, int start_vertex)
{
    vector<int> vertices = graph.get_vertices();

    if (vertices.size() < 2) 
    { 
        printf("-\n"); 
        return vector<int> {}; 
    }
    auto it = find(vertices.begin(), vertices.end(), start_vertex);
    vertices.erase(it);
    int current = start_vertex;
    vector<int> Path;
    Path.push_back(current);

    while (Path.size() != vertices.size() + 1)
    {
        vector<int> adjacent_vertices = graph.get_adjacent_vertices(current);
        double dist = numeric_limits<double>::infinity();
        int next;
        for (int i = 0; i < adjacent_vertices.size(); i++)
        {
            if (find(Path.begin(), Path.end(), adjacent_vertices[i]) == Path.end() && graph.edge_weight(current, adjacent_vertices[i]) < dist)
            {
                dist = graph.edge_weight(current, adjacent_vertices[i]);
                next = adjacent_vertices[i];
            }
        }
        if (dist == numeric_limits<double>::infinity()) return vector<int> {}; 
        Path.push_back(next);
        current = next;
    }

    //Path.push_back(start_vertex);

    if (Path.size() > 0) 
        printf("%f\n", Length(graph, Path));
    else 
        printf("-\n");
    return Path;
}


double LowerBound(const Graph& graph, vector<int> Visited) {
    //сначала проходимся по visited и находим для каждой вершины оттуда два смежных с ней ребра с 
    //минимальный весом, все веса складываем в sum, потом проходимся по оставшимся вершинам из vertices 
    //и также находим для каждой вершины два смежных ребра с минимальными весами и суммируем в sum

    vector<int> vertices = graph.get_vertices();
    vector<int> adjacent_vertices;

    double dist1, dist2;
    double sum = 0;
    //printf("\n! ");
    //for (int i = 0; i < Visited.size(); i++) printf("%d ", Visited[i]);
    //printf("!\n");
    for (int i = 0; i < Visited.size(); i++)
    {

        adjacent_vertices = graph.get_adjacent_vertices(Visited[i]);
        dist1 = numeric_limits<double>::infinity();
        dist2 = numeric_limits<double>::infinity(); //dist1 <= dist2

        for (int j = 0; j < adjacent_vertices.size(); j++)
            //if (!graph.has_edge(Visited[i], adjacent_vertices[j])) printf("alarm");
            if (graph.edge_weight(Visited[i], adjacent_vertices[j]) <= dist1)
            {
                dist2 = dist1;
                dist1 = graph.edge_weight(Visited[i], adjacent_vertices[j]);
            }
            else if (graph.edge_weight(Visited[i], adjacent_vertices[j]) <= dist2)
                dist2 = graph.edge_weight(Visited[i], adjacent_vertices[j]);

        sum += dist1 + dist2;
        auto it = find(vertices.begin(), vertices.end(), Visited[i]);
        vertices.erase(it);
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        adjacent_vertices = graph.get_adjacent_vertices(vertices[i]);
        dist1 = numeric_limits<double>::infinity();
        dist2 = numeric_limits<double>::infinity(); //dist1 <= dist2

        for (int j = 0; j < adjacent_vertices.size(); j++)
            //if (!graph.has_edge(vertices[i], adjacent_vertices[j])) printf("alarm");
            if (graph.edge_weight(vertices[i], adjacent_vertices[j]) <= dist1)
            {
                dist2 = dist1;
                dist1 = graph.edge_weight(vertices[i], adjacent_vertices[j]);
            }
            else if (graph.edge_weight(vertices[i], adjacent_vertices[j]) <= dist2)
                dist2 = graph.edge_weight(vertices[i], adjacent_vertices[j]);

        sum += dist1 + dist2;
    }
    return sum / 2;

}

vector<int> MinPath(const Graph& graph, vector<int> A, vector<int> B)
{
    double lenA = 0;
    double lenB = 0;

    for (int i = 0; i < A.size() - 1; i++)
    {
        if (!graph.has_edge(A[i], A[i + 1]))
        {
            lenA = numeric_limits<double>::infinity();
            break;
        }
        lenA += graph.edge_weight(A[i], A[i + 1]);
    }
    lenA += graph.edge_weight(A[A.size()-1], A[0]);
    for (int i = 0; i < B.size() - 1; i++)
    {
        if (!graph.has_edge(B[i], B[i + 1]))
        {
            lenB = numeric_limits<double>::infinity();
            break;
        }
        lenB += graph.edge_weight(B[i], B[i + 1]);
    }
    lenB += graph.edge_weight(B[B.size() - 1], B[0]);
    if (lenA == numeric_limits<double>::infinity() && lenB == numeric_limits<double>::infinity()) 
        return vector<int> {};
    if (lenA > lenB) 
        return B;
    else 
        return A;
}

vector<int> BnB(const Graph& graph, vector<int> Visited, vector<int> BestPath)
{
    vector<int> vertices = graph.get_vertices();
    if (vertices.size() == Visited.size()) 
        return MinPath(graph, BestPath, Visited);
    vector<int> VNext;
    vector<int> Path;

    for (int i = 0; i < vertices.size(); i++)
    {
        if (find(Visited.begin(), Visited.end(), vertices[i]) != Visited.end()) continue;
        VNext = Visited;
        VNext.push_back(vertices[i]);
        if (Length(graph, BestPath) == numeric_limits<double>::infinity() || LowerBound(graph, VNext) == numeric_limits<double>::infinity())
            return vector<int> {};
        
        if (LowerBound(graph, VNext) < Length(graph, BestPath))
        {
            Path = BnB(graph, VNext, BestPath);
            BestPath = MinPath(graph, BestPath, Path);
        }
    }
    return BestPath;
}


//метод ветвей и границ 
vector<int> tsp_Bnb(const Graph& graph, int start_vertex) {

    vector<int> BestPath = graph.get_vertices();
    if (BestPath.size() < 2) 
    { 
        printf("-\n");
        return vector<int> {}; 
    }
    if (BestPath.size() == 2 && graph.has_edge(BestPath[0], BestPath[1])) 
    { 
        printf("%f\n", Length(graph, BestPath)); 
        return BestPath; 
    }
    if (BestPath.size() == 2 && !graph.has_edge(BestPath[0], BestPath[1])) 
    { 
        printf("-\n"); 
        return vector<int> {}; 
    }

    auto it = find(BestPath.begin(), BestPath.end(), start_vertex);
    BestPath.erase(it);
    BestPath.insert(BestPath.begin(), start_vertex);

    vector<int> Visited;
    Visited.push_back(start_vertex);
    vector<int> result = BnB(graph, Visited, BestPath);
    for (int i = 0; i < result.size(); i++) 
        printf("%d ", result[i]);
    printf("\n");
    if (result.size() > 0) 
        printf("%f\n", Length(graph, result));
    else 
        printf("-\n");
    return result;
}


//полный перебор 
vector<int> tsp_brute(const Graph& graph, int start_vertex) {
    vector<int> result = {};
    vector<int> vertices = graph.get_vertices(); //завели вектор, в котором первый и последний элементы это start_vertex
    //а всё что между ними мы будем переставлять 

    if (vertices.size() < 2) 
    { 
        printf("-\n");
        return result; 
    }

    auto it = find(vertices.begin(), vertices.end(), start_vertex);
    vertices.erase(it);
    vertices.insert(vertices.begin(), start_vertex);
    vertices.push_back(start_vertex);
    sort(vertices.begin() + 1, vertices.end() - 1);

    double distance = numeric_limits<double>::infinity();
    double prom = 0;

    do {
        for (int i = 0; i < vertices.size() - 1; i++)
            if (graph.has_edge(vertices[i], vertices[i + 1]))
                prom += graph.edge_weight(vertices[i], vertices[i + 1]);
            else 
            {
                prom = numeric_limits<double>::infinity();
                break;
            }
        if (prom < distance)
        {
            distance = prom;
            result = vertices;
        }
        prom = 0;
    } while (next_permutation(vertices.begin() + 1, vertices.end() - 1));

    if (result.size() != 0) 
        result.erase(result.end() - 1);
    for (int i = 0; i < result.size(); i++) 
        printf("%d ", result[i]);
    printf("\n");
    if (result.size() > 0) 
        printf("%f\n", Length(graph, result));
    else 
        printf("-\n");
    return result;
}


vector<int> tsp(const Graph &graph, int start_vertex) {
    // Return the shortest (with a minimal total weight) tour as an array of vertices.
    // Tour is assumed to start and end in the given start vertex.
    // Start vertex should be included in the result only once, as the first item.    
    // Return empty array if there is no tour.


    //return tsp_brute(graph, start_vertex);
    //return tsp_greedy(graph, start_vertex);
    return tsp_Bnb(graph, start_vertex);
}
