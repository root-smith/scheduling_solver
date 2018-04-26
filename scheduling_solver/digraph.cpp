#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <typeinfo>
#include <vector>

#include "digraph.hpp"

using namespace std;
using json = nlohmann::json;

Digraph::Digraph()
{
	V = 0;
	E = 0;
	next_id = 0;
}

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

double Digraph::get_weight(int v, int w) const
{
	auto it = find_if( begin(adj[v]), end(adj[v]),
					  [&w](const Edge & e){ return e.target == w;} );
	return (*it).weight;
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
		vertex_list.resize(V);
	
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

bool Digraph::add_edge(const string & s1, const string & s2, double weight)
{
	if (edge_exists(s1,s2))
		return false;
	else
	{
		int from_n = add_vertex(s1);
		int to_n = add_vertex(s2);
		
		//std::cout << "new edge, from " << from_n << " to " << to_n << '\n';
		indegree[to_n]++;
		E++;
		adj[from_n].emplace_back( Edge{from_n, to_n, weight} );
		return true;
	}
}

bool Digraph::add_edge(int v, int w)
{
	return add_edge(to_string(v), to_string(w), 0.0);
}

bool Digraph::add_edge(int v, int w, double weight)
{
	return add_edge(to_string(v), to_string(w), weight);
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
	
	ss << "edge_list:\n" << edge_list_to_string() << '\n';
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

void Digraph::add_complete_layer(const std::vector<std::string> & vs, int layer)
{
	for (const auto & s : vs)
	{
		add_vertex(s);
	}
}
void Digraph::add_complete_layer(const std::vector<std::string> & vs)
{
	add_complete_layer(vs, 0);
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
