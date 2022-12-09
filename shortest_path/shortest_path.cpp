#include "shortest_path.h"
#include <queue>
using namespace std;

vector<int> shortest_path(const Graph &graph, int start_vertex, int end_vertex) {
    priority_queue<pair<int, double>> pq;
    vector<int> dist(graph.get_vertices().size(), 10000000);

    pq.push(make_pair(start_vertex, 0));
    dist[start_vertex] = 0;
    
    while (!pq.empty())
    {

        int u = pq.top().first;
        pq.pop();

        auto adj = graph.get_adjacent_edges(u);

        for (auto i = adj.begin(); i != adj.end(); ++i) 
        {
            int v = (*i).first;
            double weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(v, dist[v]));
            }
        }
    }

    return dist;
}
