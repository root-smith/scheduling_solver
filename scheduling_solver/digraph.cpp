#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <typeinfo>
#include <vector>
#include <exception>
#include <cstdlib>
#include <ctime>

#include "digraph.hpp"

using namespace std;
using json = nlohmann::json;

Digraph::Digraph(const json& j)
{
	next_id = 0;
	
	int cnt_vert = 0;
	for (auto & vert : j["nodes"])
	{
		if (vert["data"].find("layer") != vert["data"].end() )
		{
			string s = vert["data"]["id"];
			string temp = vert["data"]["layer"];
			int i = stoi(temp);
			add_vertex(s, i);
		}
		else
		{
			string s = vert["data"]["id"];
			add_vertex(s);
		}
		++cnt_vert;
	}
	
	int cnt_edges = 0;
	for (auto & edge : j["edges"])
	{
		if (edge["data"].find("source") != edge["data"].end()
			&& edge["data"].find("target") != edge["data"].end() )
		{
			string s_source = edge["data"]["source"];
			string s_target = edge["data"]["target"];
			
			int from_n = stoi(s_source);
			int to_n = stoi(s_target);
			
			if ( edge["data"].find("weight") != edge["data"].end() )
			{
				string temp = edge["data"]["weight"];
				double weight = stod(temp);
				add_edge(from_n, to_n, weight);
			}
			else
			{
				add_edge(from_n, to_n);
			}
			++cnt_edges;
		}
	}
}

//Generate random digraph
Digraph::Digraph(int layers, int nodes)
{
	if (layers > nodes)
		throw std::logic_error("Cannot generate digraph with less than one node per layer");
	
	srand(1);
	
	vector<int> nodes_per_layer;
	int remaining_nodes = nodes - layers;
	
	for (int i = layers-1; i > 0; i--)
	{
		nodes_per_layer.push_back(1 + remaining_nodes/i);
		remaining_nodes = remaining_nodes - remaining_nodes/i;
	}
	
	nodes_per_layer.push_back(1+remaining_nodes);
	/*
	cout << "nodes_per_layer: " << '\n';
	for (auto x : nodes_per_layer)
		cout << x << ' ';
	cout << '\n';
	 */
	
	//generate complete layers:
	//for each layer
	for (auto i = 0; i < layers; i++)
	{
		//cout << "Generating layer " << i << '\n';
		if (nodes_per_layer[i] == 1)
		{
			add_vertex(to_string(i) + "-0", i);
		}
		else
		{
			//for each from node in layer
			for (auto j = 0; j < nodes_per_layer[i]; j++)
			{
				//for each from node in layer
				for (auto k = j + 1; k < nodes_per_layer[i]; k++ )
				{
					//concatenating i to node so edges have unique names
					add_edge(to_string(i) + '-' + to_string(j), to_string(i) + '-' + to_string(k), i, std::rand() % 100 / 50.0);
					add_edge(to_string(i) + '-' + to_string(k), to_string(i) + '-' + to_string(j), i, std::rand() % 100 / 50.0);
				}
			}
		}
	}
	
	if (layers > 1)
	{
		//add downward connections between layers
		// if layer is 2, layer numbers are 0 or 1, add connections from 0 only
		for (auto i = 0; i < layers - 1; i++)
		{
			//cout << "Adding connections, layer " << i << '\n';
			
			//guarantee one connection from node 0 to 0 between layers
			add_edge(to_string(i) + "-0",
					 to_string(i+1) + "-0",
					 std::rand() % 100 / 50.0);
			
			//generate random connections between layers
			vector<int> curr_layer;
			vector<int> nxt_layer;
			
			int num_connections = min(nodes_per_layer[i], nodes_per_layer[i+1]);
			
			for (int c = 0; c < nodes_per_layer[i]; c++)
				curr_layer.push_back(c);
			for (int c = 0; c < nodes_per_layer[i+1]; c++)
				nxt_layer.push_back(c);
			
			std::random_shuffle ( curr_layer.begin(), curr_layer.end() );
			std::random_shuffle ( nxt_layer.begin(), nxt_layer.end() );

			for (auto j = 0; j < num_connections; j++)
			{
				add_edge(to_string(i) + '-' + to_string(curr_layer[j]),
						 to_string(i+1) + '-' + to_string(nxt_layer[j]),
						 std::rand() % 100 / 50.0);
			}
		}
	}
}

void Digraph::add_complete_layer(const std::vector<std::string> & vs, int layer)
{
	for (const auto & s : vs)
	{
		add_vertex(s);
	}
}

double Digraph::get_weight(int v, int w) const
{
	auto it = find_if( begin(adj[v]), end(adj[v]),
					  [&w](const Edge & e){ return e.target == w;} );
	return (*it).weight;
}

double Digraph::get_weight_pub(int v, int w) const
{
	return get_weight(to_string(v), to_string(w));
}

double Digraph::get_weight(std::string s1, std::string s2) const
{
	auto it_from = vertex_map.find(s1);
	auto it_to = vertex_map.find(s2);
	
	if ( it_from == vertex_map.end() || it_to == vertex_map.end())
		return false;
	int id_from = it_from->second;
	int id_to = it_to->second;
	
	auto it = find_if( begin(adj[id_from]), end(adj[id_from]),
					  [&id_to](const Edge & e)
					  {
						  return e.target == id_to;
					  } );
	//if not unfound, return true
	if ( it != end(adj[id_from]) )
		return (*it).weight;
	return -1;
}

bool Digraph::map_insert(std::string s, int i)
{
	auto res = vertex_map.insert( std::make_pair(s, i) );
	return res.second;
}

bool Digraph::vertex_exists(string s) const
{
	auto it = vertex_map.find(s);
	
	return (it != vertex_map.end());
}

bool Digraph::vertex_exists(int i) const
{
	return vertex_exists(std::to_string(i));
}

bool Digraph::edge_exists(const string & s1, const string & s2) const
{
	auto it_from = vertex_map.find(s1);
	auto it_to = vertex_map.find(s2);
	
	if ( it_from == vertex_map.end() || it_to == vertex_map.end())
		return false;
	int id_from = it_from->second;
	int id_to = it_to->second;
	
	auto it = find_if( begin(adj[id_from]), end(adj[id_from]),
					  [&id_to](const Edge & e)
					  {
						  return e.target == id_to;
					  } );
	//if not unfound, return true
	return ( it != end(adj[id_from]) );
}

bool Digraph::edge_exists(int v, int w) const
{
	return edge_exists(to_string(v), to_string(w));
}

int Digraph::get_id(const string & s)
{
	auto it = vertex_map.find(s);
	if (it != vertex_map.end())
		return it->second;
	else
		return -1;
}

int Digraph::get_id(int i)
{
	return get_id(std::to_string(i));
}

int Digraph::add_vertex(const string & s, int layer)
{
	//returns vertex id
	
	if (vertex_exists(s))
	{
		return vertex_map.find(s)->second;
	}
	else
	{
		++V;
		adj.resize(V);
		indegree.resize(V);
		vertex_map.insert(std::make_pair(s, next_id));
	
		vertex_list.emplace_back( Vertex{next_id, s, layer} );
		++next_id;
		
		return (next_id - 1);
	}
}

int Digraph::add_vertex(const std::string & s)
{
	return add_vertex(s, 0);
}
int Digraph::add_vertex(int i, int layer)
{
	return add_vertex(to_string(i), layer);
}

int Digraph::add_vertex(int i)
{
	return add_vertex(to_string(i));
}

bool Digraph::add_edge(const string & s1, const string & s2, int layer, double weight)
{
	if (edge_exists(s1,s2))
		return false;
	else
	{
		int from_n = add_vertex(s1, layer);
		int to_n = add_vertex(s2, layer);
		
		//std::cout << "new edge, from " << from_n << " to " << to_n << '\n';
		indegree[to_n]++;
		E++;
		adj[from_n].emplace_back( Edge{from_n, to_n, weight} );
		return true;
	}
}

bool Digraph::add_edge(const string & s1, const string & s2, double weight)
{
	return add_edge(s1, s2, 0, weight);
}

bool Digraph::add_edge(int v, int w, int layer, double weight)
{
	return add_edge(to_string(v), to_string(w), layer, weight);
}

bool Digraph::add_edge(int v, int w, double weight)
{
	return add_edge(to_string(v), to_string(w), weight);
}

bool Digraph::add_edge(int v, int w)
{
	return add_edge(to_string(v), to_string(w), 0.0);
}



json Digraph::to_json() const
{
	
	int cnt_edge = 0;
	//const <vector<vector<int>> edge_list = get_adj_list();
	const auto edge_list = Digraph::get_edge_list();
	map<string, pair<int, int>> m;
	
	for (auto i : edge_list)
		m.emplace(to_string(cnt_edge++), i );
	
	//generate vertex list from edge list
	vector<int> v_list;
	for (auto i : edge_list)
	{
		v_list.push_back(i.first);
		v_list.push_back(i.second);
	}
	
	json j;
	j["edge_list"] = m;
	j["edges"] = cnt_edge;
	j["vertices"] = v_list.size();
	
	//cout << "j: " << j << '\n';
	
	return j;
}

vector<vector<int>> Digraph::get_adj_list() const
{
	//returns internal vector<vector<Edge>> as vector<vector<int>>
	//where int is adjacent node IDs
	vector<vector<int>> ret;
	
	for (auto v : adj)
	{
		vector<int> t;
		for (Edge e : v)
			t.emplace_back(e.target);
		ret.push_back(t);
	}
	return ret;
}

vector<pair<int, int>> Digraph::get_edge_list() const
{
	
	vector<pair<int, int>> edge_list;
	
	//adj is std::vector<std::vector<Edge>>
	for (auto v : adj)
		for(auto e : v)
			edge_list.emplace_back(pair<int,int>{e.source, e.target});
	
	return edge_list;
}

vector<Edge> Digraph::get_edge_list_as_edge() const
{
	unordered_set<Edge> s;
	
	for (auto v : adj)
		for (auto e : v)
			s.insert(e);
	
	vector<Edge> ret(s.begin(), s.end());
	
	return ret;
}

string Digraph::edge_list_to_string() const
{
	auto edge_list = Digraph::get_edge_list();
	string s;
	
	for (auto vertex: edge_list)
	{
		s.append( "<" + to_string(vertex.first) + "," + to_string(vertex.second) + ">\n");
	}
	return s;
}

vector<int> Digraph::get_vertex_list() const
{
	//generate vertex list from edge list
	auto edge_list = get_edge_list();
	vector<int> v_list;
	
	for (auto i : edge_list)
	{
		v_list.push_back(i.first);
		v_list.push_back(i.second);
	}
	return v_list;
}

stringstream Digraph::describe() const
{
	stringstream ss;
	
	auto v_list = get_vertex_list();
	auto edge_list = get_edge_list();
	
	//ss << "edge_list:\n" << edge_list_to_string() << '\n';
	ss << "edge_list.size(): " << edge_list.size() << '\n';
	ss << "Edges: " << get_e() << '\n';
	ss << "Vertices: " << get_v() << '\n';
	ss << "vertex_list.size(): " << vertex_list.size() << '\n';
	ss << "adj.size(): " << adj.size() << '\n';
	ss << "adj list: \n";
	
	for (auto v : adj)
	{
		for (Edge e : v)
			ss << e.target << ' ';
		ss << '\n';
	}
	return ss;
}

bool is_valid_path(const Digraph & G, const vector<int> & v)
{
	bool flag = true;
	
	for (size_t i = 0; i < v.size()-1; i++)
		if (!G.edge_exists(v[i],v[i+1]))
			flag = false;
	return flag;
}



bool is_valid_graph(const Digraph & G)
{
	auto edge_list = G.get_edge_list();
	vector<int> v_list;
	
	for (auto i : edge_list)
	{
		v_list.push_back(i.first);
		v_list.push_back(i.second);
	}
	
	if (edge_list.size() == G.get_e() && v_list.size() == G.adj.size() && G.adj.size() == G.get_v())
		return true;
	else
		return false;
}

double get_path_cost(const Digraph & G, const std::vector<int> & vi)
{
	double ret = 0.00;
	
	for (auto i = 0; i < vi.size()-1; i++)
	{
		double d = G.get_weight(vi[i], vi[i+1]);
		ret += d;
	}
	return ret;
}

int Digraph::cnt_indegree_zeroes() const
{
	int cnt = 0;
	for (auto i : indegree)
	{
		if (i == 0)
			++cnt;
	}
	
	return cnt;
}

vector<int> Digraph::get_layer_zero() const
{
	vector<int> ret;
	
				//std::vector<Vertex>
	for (auto v : vertex_list)
	{
		//cout << "Vertex ID: " << v.UID << " pubic ID: " << v.public_id << " layer: " << v.layer << '\n';
		if (v.layer == 0)
		{
			ret.push_back(v.UID);
		}
	}
	return ret;
}
