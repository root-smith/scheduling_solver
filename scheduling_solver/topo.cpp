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
	cout << "G.get_V() is " << G.get_v() << '\n';
	
	for (auto i : visited)
		visited[i] = false;
	
	vector<int> indegree = G.indegree;
	for (auto i : indegree)
		cout << i << ' ';
	cout << '\n';
	
	//adj is a copy of G.adj with weights removed
	vector<vector<int>> adj;
	adj.resize(G.adj.size());
	/*
	 for (size_t i = 0; i < G.adj.size(); i++ )
	 for (size_t j = 0; j < G.adj[i].size(); j++)
	 adj[i].push_back(G.adj[i][j].to_n);
	 */
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


/*
 
 All topological sorts:
 For each vertex, make temp indegree vector
 Find all vertices where indegree is 0. "Top"
 For each Top
 If not visited
 Reduce indegree of adjacent vertices
 add vertex to res
 mark visited true
 alltopologicalSortUtil(res, visited);
 
 
 //  Main recursive function to print all possible
 //  topological sorts
 void Graph::alltopologicalSortUtil(vector<int>& res,
 bool visited[])
 {
 // To indicate whether all topological are found
 // or not
 bool flag = false;
 
 for (int i = 0; i < V; i++)
 {
 //  If indegree is 0 and not yet visited then
 //  only choose that vertex
 if (indegree[i] == 0 && !visited[i])
 {
 //  reducing indegree of adjacent vertices
 list<int>:: iterator j;
 for (j = adj[i].begin(); j != adj[i].end(); j++)
 indegree[*j]--;
 
 //  including in result
 res.push_back(i);
 visited[i] = true;
 alltopologicalSortUtil(res, visited);
 
 // resetting visited, res and indegree for
 // backtracking
 visited[i] = false;
 res.erase(res.end() - 1);
 for (j = adj[i].begin(); j != adj[i].end(); j++)
 indegree[*j]++;
 
 flag = true;
 }
 }
 
 //  We reach here if all vertices are visited.
 //  So we print the solution here
 if (!flag)
 {
 for (int i = 0; i < res.size(); i++)
 cout << res[i] << " ";
 cout << endl;
 }
 }
 
 ////
 
 //  The function does all Topological Sort.
 //  It uses recursive alltopologicalSortUtil()
 void Graph::alltopologicalSort()
 {
 // Mark all the vertices as not visited
 bool *visited = new bool[V];
 for (int i = 0; i < V; i++)
 visited[i] = false;
 
 vector<int> res;
 alltopologicalSortUtil(res, visited);
 }
 */

