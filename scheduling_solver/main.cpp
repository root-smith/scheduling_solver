#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

#include "digraph.hpp"
#include "json.hpp"

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
	
	cout << d.describe().str();
	
	return 0;
}
