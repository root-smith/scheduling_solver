#pragma once

#include <vector>
#include <sstream>
#include "dfs.hpp"

class hamiltonian_path
{
private:
	int num_paths;
	int attempts;
	std::vector<bool> marked;
	std::vector<std::vector<int>> paths;
	std::vector<int> candidate;
	
	void dfs(const Digraph & G, int v, int depth, std::vector<int> candidate);
	
public:
	hamiltonian_path(const Digraph & G);
	
	int get_num_paths() {return num_paths; };
	int get_attempts() {return attempts; };
	std::vector<std::vector<int>> get_paths() {return paths; };
	
	
};
