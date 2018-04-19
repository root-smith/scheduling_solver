#pragma once

#include <vector>
#include "digraph.hpp"

double dijkstra_sp(const Digraph & G, int s, int target);
std::vector<int> dijkstra_sp_ret(const Digraph & G, int s, int target);
void myget_path (const std::vector<int> & candidate, int j);
