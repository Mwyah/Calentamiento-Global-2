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

	void findMST(std::ostream& os);

private:
	std::vector<Vertex> vertices;
};


#endif