//
// Vertex.hpp
//

#ifndef _CMG2_VERTEX_HPP_
#define _CMG2_VERTEX_HPP_

#include <string>


class Vertex final {
public:
	Vertex(std::string name, float x, float y) : _name(name), _x(x), _y(y) {}

	inline std::string name() const { return _name; }
	inline float x() const { return _x; }
	inline float y() const { return _y; }

private:
	std::string _name;
	float _x = 0;
	float _y = 0;
};


inline bool operator==(const Vertex& a, const Vertex& b) {
	return (a.name() == b.name()) || (a.x() == b.x() && a.y() == b.y());
}

inline bool operator!=(const Vertex& a, const Vertex& b) { return !(a == b); }


#endif