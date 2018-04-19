#pragma once

struct Edge
{
	int from_n;
	int to_n;
	double weight;

	bool operator==(const Edge & other ) const
	{
		return (from_n == other.from_n && to_n == other.to_n);
	}
	
};

namespace std {
	template<>
	struct std::hash<Edge>
	{
		size_t operator()(const Edge & e) const
		{
			return ((hash<int>()(e.from_n+80000) ^ (hash<int>()(e.to_n) << 1)) >> 1);
		}
	};
}
