#pragma once

#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include "json.hpp"
#include "edge.hpp"

using json = nlohmann::json;

class Digraph
{
private:
	int V; 					//number of vertices
	int E;					//number of edges
	int next_id = 0;		//next vertex ID
	int num_layers = 0;
	
	struct Vertex
	{
		int UID;
		std::string public_id;
		int layer = 0;
	};
	
	int get_id(const std::string & s);
	int get_id(int i);
	
public:
	Digraph();
	Digraph(const json& j);
	
	
	std::vector<std::vector<Edge>> adj;					//adjacency list for vertex v
	std::vector<int> indegree;							//indegree[v] = indegree of vertex v
	std::vector<Vertex> vertex_list;
	std::unordered_map<std::string, int> vertex_map;	//maps vertex public id to private id
	
	/* Accessors */
	int get_v() const { return V; }
	int get_e() const { return E; }
	double get_weight(const Edge & e) const { return e.weight; }
	size_t get_outdegree(int v) const { return adj[v].size(); }
	size_t get_indegree(int v) const { return indegree[v]; }
	int get_num_layers() const { return num_layers; }
	
	//returns edge weight based on two vertex IDs
	double get_weight(int v, int w) const;
	
	/* adders. there is probably a real term for this */
	bool map_insert(std::string, int);
	bool add_edge(int v, int w);
	bool add_edge(int v, int w, double weight);
	bool add_edge(const std::string & s1, const std::string & s2);
	bool add_edge(const std::string & s1, const std::string & s2, double weight);
	
	int add_vertex(const std::string & s, int layer);
	int add_vertex(const std::string & s);
	int add_vertex(int i, int layer);
	int add_vertex(int i);
	
	void add_complete_layer(const std::vector<std::string> & vs, int layer);
	void add_complete_layer(const std::vector<std::string> & vs);
	
	/* predicates */
	bool edge_exists(int v, int w) const;
	bool edge_exists(const std::string & s1, const std::string & s2) const;
	
	bool vertex_exists(std::string s) const;
	bool vertex_exists(int v) const;
	
	/* Output */
	json to_json() const;
	std::vector<std::vector<int>> get_adj_list() const;
	std::vector<std::pair<int, int>> get_edge_list() const;
	std::vector<Edge> get_edge_list_as_edge() const;
	std::vector<int> get_vertex_list() const;
	std::string edge_list_to_string() const;
	std::stringstream describe() const; //make non-member
};

bool is_valid_path(const Digraph & G, const std::vector<int> & v);
bool is_valid_graph(const Digraph & G);
double get_path_cost(const Digraph & G, const std::vector<int> & vi);
