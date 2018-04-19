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
	
	//create depth first order
	int w = 6;
	dfs mydfs = dfs(d);
	cout << setw(w) << 'v' << setw(w) << "pre" << setw(w) << "post" << '\n';
	cout << "--------------------\n";
	for (int v = 0; v < d.get_v(); v++) {
		cout << setw(w) << v << setw(w) << mydfs.preorder[v] << setw(w) << mydfs.postorder[v] << '\n';
	}
	cout << '\n';
	
	cout << "E: " << d.get_e() << "; V: " << d.get_v() << '\n';
	cout << '\n';
	
	mydfs.check();
	
	// test topo
	
	Topological ts = Topological(d);
	cout << "Topological sort: \n";
	for (int i = 0; i < ts.order.size(); i++)
	{
		if (i != 0)
			cout << " => ";
		cout << ts.order[i];
	}
	cout << '\n';
	
	//create all topological sorts
	vector<vector<int>> all_tsorts = all_topological_sorts(d);
	
	cout << '\n';
	cout << all_tsorts.size() << " unique topological sorts generated.\n";
	
	if (all_tsorts.size() > 10)
	{
		cout << "Listing first 10 topological sorts: \n";
		for (auto i : Range<0, 10>())
		{
			for (auto j : all_tsorts[i])
				cout << j << ' ';
			cout << '\n';
		}
	}
	else
	{
		print_vec_of_vec(all_tsorts);
	}
	cout << '\n';
	
	return 0;
}
