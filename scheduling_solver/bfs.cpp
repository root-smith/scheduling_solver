#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

#include "digraph.hpp"
#include "bfs.hpp"

using namespace std;

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(Digraph & G, int s) : G(&G)
{
	marked.resize(G.get_v());
	dist_to.resize(G.get_v());
	edge_to.resize(G.get_v());
	
	for (int i = 0; i < G.get_v(); i++)
	{
		dist_to[i] = (int_max);
	}
	
	bfs(G, s);
}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(Digraph & G, vector<int> sources)
{
	//TODO: this
	//BFS from multiple sources
}

void BreadthFirstDirectedPaths::bfs(Digraph & G, int s)
{
	queue<int> q;
	marked[s] = true;
	dist_to[s] = 0;
	q.push(s);
	
	while (!q.empty() )
	{
		int v = q.front();
		q.pop();
		for (int w = 0; w < G.adj.size(); w++)
		{
			if(!marked[w] )
			{
				edge_to[w] = v;
				dist_to[w] = dist_to[v] + 1;
				marked[w] = true;
				q.push(w);
			}
		}
	}
}

bool BreadthFirstDirectedPaths::has_path_to(int v)
{
	//validate_vertex(v);
	return marked[v];
	
}
int BreadthFirstDirectedPaths::get_dist_to(int v)
{
	//validate_vertex(v);
	return dist_to[v];
}

stack<int> BreadthFirstDirectedPaths::path_to(int v)
{
	//validate_vertex(v);
	
	stack<int> path;
	
	if (!has_path_to(v))
	{
		// TODO: add exception handling
		cout << "No path exists.\n";
		path.push(-1);
	} else
	{
		int x = 0;
		for (x = v; dist_to[x] != 0; x = edge_to[x])
			path.push(x);
		path.push(x);
	}
	return path;
}
