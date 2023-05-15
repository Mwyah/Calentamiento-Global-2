//
// VertexParser.hpp
//

#ifndef _CMG2_VERTEX_PARSER_HPP_
#define _CMG2_VERTEX_PARSER_HPP_

#include <istream>
#include "Vertex.hpp"


class VertexParser final {
public:
	VertexParser() = delete;

	static Vertex parse(std::istream& is);
};


#endif