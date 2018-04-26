#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

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
	
	//cout << d.describe().str();
	/*
	//create depth first order
	int w = 6;
	dfs mydfs = dfs(d);
	cout << setw(w) << 'v' << setw(w) << "pre" << setw(w) << "post" << '\n';
	cout << "--------------------\n";
	for (int v = 0; v < d.get_v(); v++) {
		cout << setw(w) << v << setw(w) << mydfs.preorder[v] << setw(w) << mydfs.postorder[v] << '\n';
	}
	cout << '\n';
	*/
	cout << '\n';
	
	cout << "0 -> 1 : " << d.get_weight(0,1) << '\n';
	cout << "1 -> 2 : " << d.get_weight(1,2) << '\n';
	
	
	Timer htime;
	htime.start();
	
	hamiltonian_path hpath = hamiltonian_path(d);
	cout << "Number of Hamiltionian Paths: " << hpath.get_num_paths() << " found out of " << hpath.get_attempts() << '\n';
	
	htime.stop();
	cout << "Runtime: " << htime.elapsed_ms() << " ms\n";
	
	auto vvi = hpath.get_paths();
	for (int i = 0; i < 4; i++)
	{
		for (auto x : vvi[i])
			cout << x << " -> ";
		cout << ": " << get_path_cost(d, vvi[i]) << '\n';
	}
	
	//dijkstra_sp d = dijkstra_sp(d);
	
	return 0;
}
