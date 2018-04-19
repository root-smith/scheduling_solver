#pragma once

#include <vector>
#include <deque>

#include "digraph.hpp"

class dfs
{
public:
	std::vector<bool> marked;
	std::vector<int> pre;
	std::vector<int> post;
	std::vector<int> preorder;
	std::vector<int> postorder;
	std::vector<int> reverse_postorder;
	int pre_counter;
	int post_counter;
	
	//public
	dfs(const Digraph & G);
	
	// run DFS in edge-weighted digraph G from vertex v and compute preorder/postorder
	void run_dfs(const Digraph & G, int v);
	
	//returns the pre/postorder number of vertex v
	int get_pre(int v) const { return pre[v]; }
	int get_post(int v) const { return post[v]; }
	
	bool check();
	void validate_vertex(int v);
};
