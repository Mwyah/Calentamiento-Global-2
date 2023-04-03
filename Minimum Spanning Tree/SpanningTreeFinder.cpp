//
// SpanningTreeFinder.cpp
//

#include "SpanningTreeFinder.hpp"


bool SpanningTreeFinder::addVertex(VertexParser::Output data) {
	Vertex v(data);

	auto isConflict = [v](Vertex v2){ return (v2.name() == v.name()) ||
	(v2.x() == v.x() && v2.y() == v.y()); };

	if (std::find_if(vertices.begin(), vertices.end(), isConflict) == 
		vertices.end()) {

		vertices.push_back(v);

		return true;
	}

	return false;
}
