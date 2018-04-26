#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <limits>

#include "digraph.hpp"
#include "json.hpp"
#include "dfs.hpp"
#include "topo.hpp"
#include "util.hpp"
#include "dijkstra_sp.hpp"
#include "hamiltonian_path.hpp"
#include "timer.hpp"

using namespace std;
using json = nlohmann::json;

template <typename T>
void print_vec_of_vec(const vector<T> & x)
{
	for (auto i : x)
	{
		for (auto j : i)
			cout << j << ' ';
		cout << '\n';
	}
}

int main()
{
	//load json file with list of graph edges
	std::ifstream i("graph.json");
	
	json jin;
	i >> jin;
	
	replace( jin.begin(), jin.end(), '[', '{' );
	replace( jin.begin(), jin.end(), ']', '}' );
	
	//create digraph object from json
	Digraph d(jin);
	
	Timer htime;
	htime.start();
	
	hamiltonian_path hpath = hamiltonian_path(d);
	cout << "Number of Hamiltionian Paths: " << hpath.get_num_paths() << " found out of " << hpath.get_attempts() << '\n';
	
	htime.stop();
	cout << "Runtime, find all Hamiltionian Paths: " << htime.elapsed_ms() << " ms\n";
	
	
	htime.start();
	hpath.run_shortest_path();
	htime.stop();
	cout << "Runtime, find shortest: " << htime.elapsed_ms() << " ms\n";

	cout << "Min path: " << '\n';
	for (auto i : hpath.get_shortest_path())
		cout << i << ' ';

	cout << '\n' << "Cost: " << hpath.get_sp_cost() << '\n';
	
	return 0;
}
