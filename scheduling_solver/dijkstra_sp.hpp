#pragma once

#include <vector>
#include "digraph.hpp"

double dijkstra_sp(const Digraph & G, int s, int target);
std::vector<double> dijkstra_sp_ret(const Digraph & G, int s, int target);
