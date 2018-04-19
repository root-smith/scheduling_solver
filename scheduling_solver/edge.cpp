#include <string>

#include "edge.hpp"

/*
namespace std {
	template<>
	struct std::hash<Edge>
	{
		size_t operator()(const Edge & e) const
		{
			return ((hash<float>()(e.from_n) ^ (hash<float>()(e.to_n) << 1)) >> 1);
		}
	};
}
*/
