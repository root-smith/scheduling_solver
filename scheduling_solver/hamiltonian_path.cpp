#include "hamiltonian_path.hpp"

#include <vector>
#include "dfs.hpp"

hamiltonian_path::hamiltonian_path(const Digraph & G )
{
	num_paths = 0;
	marked.resize(G.get_v());
	
	//recursive dfs from every vertex
	for (int v = 0; v < G.get_v(); v++)
	{
		if (G.indegree[v] == 0)
			dfs(G, v, 1, candidate);
	}
};

void hamiltonian_path::dfs(const Digraph & G, int v, int depth, std::vector<int> candidate)
{
	//depth = depth of recursion
	
	marked[v] = true;
	candidate.push_back(v);
	
	if (depth == G.get_v())
	{
		++num_paths;
		paths.push_back(candidate);
	}
	
	//for every vertex adjacent to v
	for (auto e : G.adj[v] )
	{
		if (!marked[e.target])
		{
			//std::cout << "searching vertex " << e.target << " at depth " << (depth+1) << '\n';
			dfs(G, e.target, depth+1, candidate); 	//backtrack if w is already part of path
		}
	}
	marked[v] = false;
	++attempts;
	candidate.pop_back();
}
