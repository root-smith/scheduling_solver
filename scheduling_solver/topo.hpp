#pragma once

#include <vector>
#include "digraph.hpp"

class Topological
{
public:
	std::vector<int> order;
	std::vector<int> rank;
	
	Topological(const Digraph & G);
	bool has_order();
	int get_rank(int v);
	void validate_vertex(int v);
	
};

std::vector<std::vector<int>> all_topological_sorts(const Digraph & G);
