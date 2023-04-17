//
// Edge.hpp
//

#ifndef _CMG2_EDGE_HPP_
#define _CMG2_EDGE_HPP_

#include "Vertex.hpp"

#include <cmath>


class Edge final {
public:
	Edge(Vertex v1, Vertex v2, size_t index1, size_t index2) {
		_v1 = index1;
		_v2 = index2;
		_length = sqrtf(powf(v1.x() - v2.x(), 2) + powf(v1.y() - v2.y(), 2));
	};

	inline size_t v1() const { return _v1; }
	inline size_t v2() const { return _v2; }
	inline float length() const { return _length; }

private:
	size_t _v1 = 0;
	size_t _v2 = 0;
	float _length = 0;
};


inline bool operator<(const Edge& a, const Edge& b) {
	return a.length() < b.length();
}


#endif