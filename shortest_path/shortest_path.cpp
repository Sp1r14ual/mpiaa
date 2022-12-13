#include "shortest_path.h"
#include <queue>
#include <vector>
#define N 1000000000
using namespace std;


vector<int> build_path(vector<int>& prev, int start_vertex, int end_vertex)
{
    vector<int> path;
    int i = end_vertex;
    path.push_back(end_vertex);
    while (i != start_vertex)
    {
        i = prev[i];
        if (i == N || i == end_vertex)
            return vector<int> {};
        path.insert(path.begin(), i);
    }

    return path;
}

vector<int> shortest_path(const Graph &graph, int start_vertex, int end_vertex) {
    int v_size = graph.get_vertices().size();
    if (v_size == 0 || start_vertex == end_vertex)
        return vector<int> {};

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    vector<double> dist(v_size, N);
    vector<int> prev(v_size, N);

    pq.push(make_pair(0, start_vertex));
    dist[start_vertex] = 0;
    
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (u == N)
            return build_path(prev, start_vertex, end_vertex);

        vector<pair<int, double>> adj = graph.get_adjacent_edges(u);
        for (auto i = adj.begin(); i != adj.end(); ++i)
        {
            int v = (*i).first;
            double weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return build_path(prev, start_vertex, end_vertex);
}
