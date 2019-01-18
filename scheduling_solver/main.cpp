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

	Digraph d(jin);
	
	Timer htime;
	
	htime.start();
	int nodes = 20;
	int layers = 5;
	Digraph rd(layers, nodes);
	htime.stop();
	
	cout << "\nRuntime, graph generation: " << htime.elapsed_ms() << " ms\n";
	cout << "\nRandomly Generated Digraph\nVertices: " << rd.get_v() << ", Edges: " << rd.get_e() << ", Layers: " << layers << '\n';
	
	htime.start();
	hamiltonian_path rdpath = hamiltonian_path(rd);
	cout << "\nNumber of Hamiltionian Paths: " << rdpath.get_num_paths() << " found out of "
		<< rdpath.get_attempts() << '\n';
	htime.stop();
	
	cout << "\nRuntime, find all Hamiltionian Paths: " << htime.elapsed_ms() << " ms\n";
	
	htime.start();
	rdpath.run_shortest_path();
	htime.stop();
	
	cout << "Runtime, find shortest: " << htime.elapsed_ms() << " ms\n";
	
	cout << "\nMin path: " << '\n';
	for (auto i : rdpath.get_shortest_path())
		cout << i << ' ';
	
	cout << '\n' << "Cost: " << rdpath.get_sp_cost() << '\n';
	cout << '\n';
	
	return 0;
}

/*
 cout << '\n';
 for (int i = 0; i < nodes - 1; i++)
 {
	 for (int j = 1; j < nodes; j++)
	 {
	 	cout << "weight betwen node " << i << " and " << j << ": "
 		<< rd.get_weight("0-" + to_string(i), "0-"+to_string(i+1)) << '\n';
	 }
 }
 */
