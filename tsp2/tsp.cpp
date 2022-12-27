#include "tsp.h"
#include <iostream>
#include <chrono>
#include <vector>

double Length(const Graph& graph, std::vector<int> Path)
{
	double len = 0;

	for (int i = 0; i < Path.size() - 1; i++) 
		len += graph.edge_weight(Path[i], Path[i + 1]);
	len += graph.edge_weight(Path[Path.size() - 1], Path[0]);
	return len;
}

std::vector<int> Transform(std::vector<int> CurrentPath, int A, int B, int C, int D)
{
	std::vector<int> res;
	res.push_back(A);
	int s;
	for (int i = 0; i < CurrentPath.size(); i++)
		if (CurrentPath[i] == C)
		{
			s = i;
			break;
		}
	do 
	{
		res.push_back(CurrentPath[s]);
		s--;
	} while (CurrentPath[s] != B);
	res.push_back(CurrentPath[s]);
	for (int i = 0; i < CurrentPath.size(); i++)
		if (CurrentPath[i] == D)
		{
			s = i;
			break;
		}
	for (int i = s; i < CurrentPath.size(); i++)
		res.push_back(CurrentPath[i]);
	return res;
}

std::vector<int> TwoOptImprove(const Graph& graph, std::vector<int> CurrentPath)
{
	int s;
	if (CurrentPath.size() % 2 == 0) 
		s = 0;
	else 
		s = 1;
	for (int i = 0; i < CurrentPath.size() - 1; i++)
	{
		int A = CurrentPath[i];
		int B = CurrentPath[i + 1];
		for (int j = i + 1; j < CurrentPath.size() - 1; j++)
		{
			int C = CurrentPath[j];
			int D = CurrentPath[j + 1];
			if (!graph.has_edge(A, B) || !graph.has_edge(C, D) || !graph.has_edge(A, C) || !graph.has_edge(B, D)) 
				return std::vector<int> {};
			double OldWeight = graph.edge_weight(A, B) + graph.edge_weight(C, D);
			double NewWeight = graph.edge_weight(A, C) + graph.edge_weight(B, D);
			if (NewWeight < OldWeight) 
				return Transform(CurrentPath, A, B, C, D);
		}
	}
	return CurrentPath;
}

std::vector<int> tsp(const Graph& graph, int start_vertex)
{
	if (graph.get_vertices().size() < 2) 
		return std::vector<int> {};

	std::vector<int> CurrentPath = graph.get_vertices();
	std::vector<int> ImprovedPath;

	while (true)
	{
		ImprovedPath = TwoOptImprove(graph, CurrentPath);
		if (ImprovedPath.size() == 0) 
			return std::vector<int> {};
		if (Length(graph, ImprovedPath) < Length(graph, CurrentPath))
			CurrentPath = ImprovedPath;
		else
		{
			printf("%f\n", Length(graph, CurrentPath));
			return CurrentPath;
		}
	}
}
