#include "min_spanning_tree.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#define N 1000000000

using namespace std;

int extract_min(vector<int>& Q, vector<double>& MinWeight)
{
	double min_dist = N;
	auto u = Q.end();
	int result = N;

	for (auto i = Q.begin(); i < Q.end(); ++i)
	{
		if (MinWeight[*i] < min_dist) {
			min_dist = MinWeight[*i];
			u = i;
			result = *i;
		}
	}

	if (u != Q.end()) {
		Q.erase(u);
	}

	return result;
}

vector<pair<int, int>> min_spanning_tree(const Graph &graph)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	auto Q = graph.get_vertices();
	if (Q.size() == 0) {
		auto t2 = std::chrono::high_resolution_clock::now();		
		auto time = std::chrono::duration<double>(t2 - t1).count();
		std::cout << "Time: " << time << " sec." << std::endl;
		return vector<pair<int, int>>{};
	}

	vector<double> MinWeight(Q.size());
	vector<int> parent(Q.size());
	for (int i = 0; i < MinWeight.size(); ++i) {
		MinWeight[i] = N;
		parent[i] = N;
	}
	MinWeight[0] = 0;

	while (!Q.empty())
	{
		int u = extract_min(Q, MinWeight);
		if (u == N)
			break;

		auto v = graph.get_adjacent_vertices(u);
		for (int i = 0; i < v.size(); ++i)
		{
			auto ability = find(Q.begin(), Q.end(), v[i]);
			if (ability != Q.end() and MinWeight[v[i]] > graph.edge_weight(u, v[i])) {
				MinWeight[v[i]] = graph.edge_weight(u, v[i]);
				parent[v[i]] = u;
			}
		}
	}

	vector<pair<int, int>> MST;
	auto v = graph.get_vertices();
	for (int i = 0; i < v.size(); ++i)
		if (parent[v[i]] != N)
			MST.push_back(make_pair(v[i], parent[v[i]]));

	auto t2 = std::chrono::high_resolution_clock::now();		
	auto time = std::chrono::duration<double>(t2 - t1).count();
	std::cout << "Time: " << time << " sec." << std::endl;
	return MST;
}
