#pragma once

struct Edge
{
	int source;
	int target;
	double weight;

	bool operator==(const Edge & other ) const
	{
		return (source == other.source && target == other.target);
	}
	
};

namespace std {
	template<>
	struct std::hash<Edge>
	{
		size_t operator()(const Edge & e) const
		{
			return ((hash<int>()(e.source) ^ (hash<int>()(e.target) << 1)) >> 1);
		}
	};
}

/*
 set[n][n] adjacency matrix
 */
