//
// Vertex.hpp
//

#ifndef _CMG2_VERTEX_HPP_
#define _CMG2_VERTEX_HPP_


class Vertex final {
public:
	Vertex(size_t ind, int x, int y) : _ind(ind), _x(x), _y(y) {}

	inline size_t ind() const { return _ind; }
	inline int x() const { return _x; }
	inline int y() const { return _y; }

private:
	size_t _ind = 0;
	int _x = 0;
	int _y = 0;
};


#endif