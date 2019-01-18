#include "hamiltonian_path.hpp"

#include <vector>
#include <algorithm>
#include <limits>
#include <exception>
#include "dfs.hpp"
#include "digraph.hpp"

hamiltonian_path::hamiltonian_path(const Digraph & G ) : graph(G)
{
	num_paths = 0;
	marked.resize(G.get_v());
	
	int cnt = graph.cnt_indegree_zeroes();
	
	std::cout << "Number of nodes with indegree of zero: " << cnt << '\n';
	
	if (cnt > 1)
	{
		throw std::logic_error("too many nodes with indegree 0");
	}
	else if (cnt == 1)
	{
		//recursive dfs from every vertex
		for (int v = 0; v < G.get_v(); v++)
		{
			if (G.indegree[v] == 0)
				dfs(v, 1, candidate);
		}
	}
	else
	{
		std::vector<int> layer_zero = graph.get_layer_zero();
		
		for (auto i : layer_zero)
		{
			dfs(i, 1, candidate);
			std::fill(marked.begin(), marked.end(), false);
		}
	}
};

void hamiltonian_path::dfs(int v, int depth, std::vector<int> candidate)
{
	//depth = depth of recursion
	
	marked[v] = true;
	candidate.push_back(v);
	
	if (depth == graph.get_v())
	{
		++num_paths;
		paths.push_back(candidate);
	}
	
	//for every vertex adjacent to v
	for (auto e : graph.adj[v] )
	{
		if (!marked[e.target])
		{
			//std::cout << "searching vertex " << e.target << " at depth " << (depth+1) << '\n';
			dfs(e.target, depth+1, candidate); 	//backtrack if w is already part of path
		}
	}
	marked[v] = false;
	++attempts;
	candidate.clear();
}

void hamiltonian_path::run_shortest_path()
{
	double min_cost = std::numeric_limits<double>::max();
	std::vector<int> min_path;
	
	//std::vector<std::vector<int>> paths;
	for (auto p : paths)
	{
		double curr = get_path_cost(graph, p);
		if ( curr <= min_cost)
		{
			min_cost = curr;
			min_path = p;
		}
	}
	shortest_path = min_path;
	sp_cost = min_cost;
}

/* Non-member Functions */

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




