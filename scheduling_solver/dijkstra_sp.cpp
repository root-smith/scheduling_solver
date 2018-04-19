#include <limits>
#include <set>
#include <vector>
#include <list>
#include <utility>
#include <iterator>

#include "digraph.hpp"
#include "edge.hpp"
#include "dijkstra_sp.hpp"

using namespace std;

double dijkstra_sp(const Digraph & G, int s, int target)
{
	//int dijkstra(const vector< vector<edge> > &graph, int source, int target)
	vector<vector<Edge>> graph = G.adj;
	
	vector<double> min_dist(G.get_e(), numeric_limits<double>::max() );
	min_dist[s] = 0;
	set<pair<int,int>> active_vertices;
	
	active_vertices.insert( {0,s} );
	
	while (!active_vertices.empty())
	{
		int where = active_vertices.begin()->second;
		
		if (where == target)
			return min_dist[where];
		
		active_vertices.erase( active_vertices.begin() );
		
		for (auto e : graph[where])
		{
			if (min_dist[e.to_n] > min_dist[where] + e.weight)
			{
				active_vertices.erase( { min_dist[e.to_n], e.to_n } );
				min_dist[e.to_n] = min_dist[where] + e.weight;
				active_vertices.insert( { min_dist[e.to_n], e.to_n } );
			}
		}
	}
	return numeric_limits<double>::max();
}


vector<double> dijkstra_sp_ret(const Digraph & G, int s, int target)
{
	//int dijkstra(const vector< vector<edge> > &graph, int source, int target)
	vector<vector<Edge>> graph = G.adj;
	
	vector<double> min_dist(G.get_v(), numeric_limits<double>::max() );
	min_dist[s] = 0;
	set<pair<int,int>> active_vertices;
	
	active_vertices.insert( {0,s} );
	
	while (!active_vertices.empty())
	{
		int where = active_vertices.begin()->second;
		
		if (where == target)
			return min_dist;
		
		active_vertices.erase( active_vertices.begin() );
		
		for (auto e : graph[where])
		{
			if (min_dist[e.to_n] > min_dist[where] + e.weight)
			{
				active_vertices.erase( { min_dist[e.to_n], e.to_n } );
				min_dist[e.to_n] = min_dist[where] + e.weight;
				active_vertices.insert( { min_dist[e.to_n], e.to_n } );
			}
		}
	}
	return min_dist;
}

