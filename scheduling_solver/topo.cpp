#include <iostream>
#include "topo.hpp"
#include "dfs.hpp"

using namespace std;

std::vector<int> order;
std::vector<int> rank;

Topological::Topological(const Digraph & G)
{
	//TODO: check for directed cycles
	
	dfs search = dfs(G);
	size_t size = search.postorder.size();
	
	if ( size > INT_MAX )
		throw std::overflow_error("Postorder size is larger than INT_MAX");
	//TODO: catch this somewhere
	int i = static_cast<int>(size);
	
	for (auto it = end(search.postorder) - 1; it != begin(search.postorder) - 1; --it )
	{
		order.push_back(*it);
		rank.push_back(--i);
	}
}

bool Topological::has_order() { return order.size() != 0; }

int Topological::get_rank(int v)
{
	if (has_order())
		return rank[v];
	else
		return -1;
}
void Topological::validate_vertex(int v)
{
	auto V = rank.size();
	if (v < 0 || v >= V)
		std::cout << "vertex " << v << " is not between 0 and " << (V-1) << '\n';
}

void all_topological_util(vector<int> & new_solution, vector<bool> & visited, vector<int> & indegree, const vector<vector<int>> & adj, vector<vector<int>> & ret)
{
	bool flag = false;
	
	for (int i = 0; i < visited.size(); i++)
	{
		//  If indegree is 0 and not yet visited then
		//  only choose that vertex
		if (indegree[i] == 0 && !visited[i])
		{
			// decrement indegree of adjacent vertices
			for (auto j : adj[i])
				indegree[j]--;
			
			//  add to result
			new_solution.push_back(i);
			visited[i] = true;
			all_topological_util(new_solution, visited, indegree, adj, ret);
			
			// resetting visited, res and indegree for
			// backtracking
			visited[i] = false;
			new_solution.erase(new_solution.end() - 1);
			for (auto j = adj[i].begin(); j != adj[i].end(); j++)
				indegree[*j]++;
			
			flag = true;
		}
	}
	
	//  Print solution
	if (!flag)
	{
		ret.push_back(new_solution);
	}
}

vector<vector<int>> all_topological_sorts(const Digraph & G)
{
	
	// Mark all the vertices as not visited
	vector<bool> visited;
	visited.resize(G.get_v());
	
	for (auto i : visited)
		visited[i] = false;
	
	vector<int> indegree = G.indegree;
	
	//adj is a copy of G.adj with weights removed
	vector<vector<int>> adj;
	adj.resize(G.adj.size());

	adj = G.get_adj_list();
	
	/*
	cout << "adj list: \n";
	for (auto i : adj)
	{
		cout << '\n';
		for (auto v : i)
			cout << v << ' ';
	}
	cout << '\n';
	 
	cout << "indegree: \n";
	for (auto i: indegree)
		cout << i << '\n';
	*/
	 
	vector<int> new_solution;
	vector<vector<int>> ret;
	all_topological_util(new_solution, visited, indegree, adj, ret);
	
	return ret;
}
