#include <vector>
#include <limits>

#include "dijkstra.hpp"


using namespace std;

Dijkstra::Dijkstra(const Digraph & G, int s)
{
	dist_to.resize(G.get_v());
	//edge_to.resize(G.get_v());
	
	vector<Edge> edge_to = G.get_edge_list_as_edge();
	
	/*
	for (DirectedEdge e : G.edges()) {
		if (e.weight() < 0)
			throw new IllegalArgumentException("edge " + e + " has negative weight");
	}
	
	distTo = new double[G.V()];
	edgeTo = new DirectedEdge[G.V()];
	
	validateVertex(s);
	
	for (int v = 0; v < G.V(); v++)
		distTo[v] = Double.POSITIVE_INFINITY;
	distTo[s] = 0.0;
	
	// relax vertices in order of distance from s
	pq = new IndexMinPQ<Double>(G.V());
	pq.insert(s, distTo[s]);
	while (!pq.isEmpty()) {
		int v = pq.delMin();
		for (DirectedEdge e : G.adj(v))
			relax(e);
	}
	
	// check optimality conditions
	assert check(G, s);
}
	 
// header:
 class Dijkstra
 {
 struct Edge
 {
 int from_n;
 int to_n;
 double weight;
 };
 
 std::vector<double> dist_to;			// distTo[v] = distance  of shortest s->v path
 std::vector<Edge> edge_to;    			// edgeTo[v] = last edge on shortest s->v path
 std::priority_queue<double> pq;			// min priority queue of vertices
 
 void relax(Edge & e);
 
 public:
 Dijkstra(const Digraph & G, int s);
 double get_dist_to(int v);
 bool has_path_to(int v);
 bool check(const Digraph & G, int s);
  */
	
	
 };
 

