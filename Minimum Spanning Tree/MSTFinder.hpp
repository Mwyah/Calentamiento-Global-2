//
// MSTFinder.hpp
//

#ifndef _CMG2_MST_FINDER_HPP_
#define _CMG2_MST_FINDER_HPP_

#include <vector>
#include <set>

#include "Edge.hpp"
#include "VertexParser.hpp"


class MSTFinder final{
public:

	bool addVertex(const Vertex& vertex);
	bool addVertex(Vertex&& vertex);

	void findMST();

	void printMST(std::ostream& os);

private:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	bool isValidMST = false;
	std::vector<Edge> MST;
	std::vector<std::set<size_t>> disjointSet;


	void fillAndSortVertices();

	auto findVertexInDisjointSet(size_t ind);
};


#endif