#pragma once

#include <vector>
#include <queue>

#include "digraph.hpp"
#include "edge.hpp"

class Dijkstra
{
	
	std::vector<double> dist_to;			// distTo[v] = distance  of shortest s->v path
	std::vector<Edge> edge_to;    			// edgeTo[v] = last edge on shortest s->v path
	std::priority_queue<double> pq;			// min priority queue of vertices
	
	void relax(Edge & e);
	
public:
	Dijkstra(const Digraph & G, int s);
	double get_dist_to(int v);
	bool has_path_to(int v);
	bool check(const Digraph & G, int s);
	
};
