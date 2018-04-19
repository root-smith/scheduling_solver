#pragma once

#include <vector>
#include <sstream>
#include "dfs.hpp"

class hamiltonian_path
{
private:
	int count;
	std::vector<bool> marked;
	std::vector<std::vector<int>> paths;
	std::vector<int> candidate;
	
	void dfs(const Digraph & G, int v, int depth);
	
public:
	hamiltonian_path(const Digraph & G);
	
	int get_count() {return count; };
	std::vector<std::vector<int>> get_paths() {return paths; };
	
	
};
