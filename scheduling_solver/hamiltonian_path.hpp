#pragma once

#include <vector>
#include <sstream>
#include "dfs.hpp"
#include "digraph.hpp"

class hamiltonian_path
{
private:
	Digraph graph;
	int num_paths = 0;
	int attempts = 0;
	std::vector<bool> marked;
	std::vector<std::vector<int>> paths;
	std::vector<int> candidate;

	void dfs(int v, int depth, std::vector<int> candidate);
	
	std::vector<int> shortest_path;
	double sp_cost;
	
public:
	hamiltonian_path(const Digraph & G);
	hamiltonian_path(const Digraph & G, int layer);
	
	void run_shortest_path();
	
	int get_num_paths() {return num_paths; };
	int get_attempts() {return attempts; };
	std::vector<std::vector<int>> get_paths() const {return paths; };
	std::vector<int> get_shortest_path() const {return shortest_path; };
	double get_sp_cost() const {return sp_cost; };
	
};

std::stringstream print_all_paths(const hamiltonian_path & hpath);

std::pair<double, std::vector<int>> get_min_path(const Digraph & G);
