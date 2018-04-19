#include <iostream>
#include <vector>
#include <algorithm>

#include "dfs.hpp"
#include "digraph.hpp"

dfs::dfs(const Digraph & G)
{
	pre.resize(G.get_v());
	post.resize(G.get_v());
	marked.resize(G.get_v());
	
	for (int v = 0; v < G.get_v(); v++)
		if (!marked[v]) run_dfs(G, v);
	
	reverse_postorder.resize(postorder.size());
	std::reverse_copy(postorder.begin(), postorder.end(), reverse_postorder.begin());
}

void dfs::run_dfs(const Digraph & G, int v)
{
	//std::cout << "Visiting node " << v << '\n';
	
	marked[v] = true;
	pre[v] = pre_counter++;
	preorder.push_back(v);
	
	std::vector<std::vector<int>> adj = G.get_adj_list();
	
	//for every int in the adjacency list for vertex v
	//int w = static_cast<int>(adj[v].size());
	for (auto i : adj[v])
	{
		if (!marked[i]) {
			run_dfs(G, i);
		}
	}
	postorder.push_back(v);
	post[v] = post_counter++;
}

bool dfs::check()
{
	// check that post(v) is consistent with post()
	int r = 0;
	for (int v : postorder)
	{
		//std::cout << "get_post: " << get_post(v) << " ; postorder: " << v << '\n';
		if (get_post(v) != r) {
			std::cout << "post(v) and post() inconsistent\n";
			return false;
		}
		r++;
	}
	
	// check that pre(v) is consistent with pre()
	r = 0;
	for (int v : preorder)
	{
		if (get_pre(v) != r) {
			std::cout << "pre(v) and pre() inconsistent\n";
			return false;
		}
		r++;
	}
	return true;
}

void dfs::validate_vertex(int v)
{
	auto V = marked.size();
	if (v < 0 || v >= V)
		std::cout << "error with dfs number of vertices < 0\n";
	if (v >= V)
		std::cout << "error with dfs number of vertices greater than max number of vertices\n";
}
