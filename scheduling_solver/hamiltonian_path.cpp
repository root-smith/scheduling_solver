#include "hamiltonian_path.hpp"

#include <vector>
#include <algorithm>
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

std::stringstream print_all_paths(const hamiltonian_path & hpath)
{
	std::stringstream ss;
	ss << "Hamiltionian Paths: \n";
	for (auto vi : hpath.get_paths())
	{
		ss << "Path:\n";
		for (auto i : vi)
			ss << i << ' ';
		ss << '\n';
	}
	return ss;
}

double get_path_cost(const Digraph & G, const std::vector<int> & vi)
{
	double ret = 0.00;
	
	for (auto i = 0; i < vi.size()-1; i++)
	{
		ret += G.get_weight(i,i+1);
	}
	
	/*
	double ret = std::accumulate(vi.begin(), vi.end(),
								[&G](int i, int j)
								{
									return G.get_weight(i,j);
								}
						   );
	 */
	
	return ret;
}
