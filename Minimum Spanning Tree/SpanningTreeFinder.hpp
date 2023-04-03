//
// SpanningTreeFinder.hpp
//

#ifndef _CMG2_SPANNING_TREE_FINDER_HPP_
#define _CMG2_SPANNING_TREE_FINDER_HPP_

#include <vector>
#include <set>

#include "Edge.hpp"
#include "VertexParser.hpp"


class SpanningTreeFinder final{
public:

	bool addVertex(VertexParser::Output data);


private:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	bool isEdgesSorted = false;
	std::vector<size_t> minSpanTree;
	std::vector<std::set<size_t>> disjointSet;

};


#endif