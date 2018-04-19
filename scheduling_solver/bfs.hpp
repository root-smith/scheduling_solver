#pragma once

#include <limits>
#include <stack>

class BreadthFirstDirectedPaths
{
private:
	int int_max = std::numeric_limits<int>::max();
	std::vector<bool> marked;
	std::vector<int> dist_to;
	std::vector<int> edge_to;
	Digraph* G;
	
	void bfs(Digraph & G, int s);	// BFS from single source
	void bfs(Digraph & G, std::vector<int> sources); // BFS from multiple sources
	void validate_vertex(int v);
	void validate_vertices(std::vector<int> vertices);
	
public:
	//Computes the shortest path from s and every other vertex in graph
	BreadthFirstDirectedPaths(Digraph & G, int s);
	
	//Computes the shortest path from any one of the source vertices
	//in sources to every other vertex in graph
	BreadthFirstDirectedPaths(Digraph & G, std::vector<int> sources);
	
	bool has_path_to(int v);
	int get_dist_to(int v);
	std::stack<int> path_to(int v);
};

