//
// Edge.hpp
//

#ifndef _CMG2_EDGE_HPP_
#define _CMG2_EDGE_HPP_

#include "Vertex.hpp"

#include <cmath>


class Edge final {
public:
	Edge(Vertex v1, Vertex v2) {
		_v1 = v1.ind();
		_v2 = v2.ind();
		_length = sqrtf((v1.x() - v2.x())^2 + (v1.y() + v2.y())^2);
	};

	inline size_t v1() const { return _v1; }
	inline size_t v2() const { return _v2; }
	inline float length() const { return _length; }

private:
	size_t _v1 = 0;
	size_t _v2 = 0;
	float _length = 0;
};


#endif