#include "hamiltonian_path.hpp"

#include <vector>
#include "dfs.hpp"

hamiltonian_path::hamiltonian_path(const Digraph & G )
{
	count = 0;
	marked.resize(G.get_v());
	candidate.resize(G.get_v());
	
	//recursive dfs from every vertex
	for (int v = 0; v < G.get_v(); v++)
		dfs(G, v, 1);
};

void hamiltonian_path::dfs(const Digraph & G, int v, int depth) //depth  = depth of recursion
{
	//std::vector<std::vector<int>> paths;
	
	marked[v] = true;
	candidate.push_back(v);
	
	if (depth == G.get_v())
	{
		++count;	//found a path
		paths.push_back(candidate);
	}
	
	//for every vertex adjacent to v
	for (auto e : G.adj[v] )
	{
		if (!marked[e.to_n])
			dfs(G, e.to_n, depth+1); 	//backtrack if w is already part of path
	}
	marked[v] = false;
	candidate.clear();
}
