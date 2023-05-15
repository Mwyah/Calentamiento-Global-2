//
// MSTFinder.cpp
//

#include "MSTFinder.hpp"

#include <algorithm>
#include <ostream>

namespace {

auto findEdgeInDisjointSet(std::vector<std::set<size_t>>& disjointSet, size_t ind) {
	for (auto it = disjointSet.begin(); it != disjointSet.end(); it++) {
		if (std::find(it->begin(), it->end(), ind) != it->end())
			return it;
	}

	return disjointSet.end();
};

}

bool MSTFinder::addVertex(const Vertex& vertex) {
	if (!vertex.name().empty() && std::find(vertices.begin(), vertices.end(), vertex) == vertices.end()) {
		vertices.push_back(vertex);
		return true;
	}

	return false;
}

void MSTFinder::findMST(std::ostream& os) {

	if (vertices.size() < 2) return;


	std::vector<Edge> edges;
	for (size_t i = 0; i<vertices.size()-1; i++) {
		for (size_t j = i+1; j<vertices.size(); j++) {
			edges.push_back(Edge(vertices[i], vertices[j], i, j));
		}
	}

	std::sort(edges.begin(), edges.end());

	std::vector<std::set<size_t>> disjointSet;
	size_t MSTSize = 0;

	for (auto& e: edges) {

		auto it1 = findEdgeInDisjointSet(disjointSet, e.v1());
		auto it2 = findEdgeInDisjointSet(disjointSet, e.v2());

		if (it1 == disjointSet.end()) {
			if (it2 == disjointSet.end())
				disjointSet.push_back({e.v1(), e.v2()});
			else
				it2->insert(e.v1());
		}
		else {
			if (it2 == disjointSet.end())
				it1->insert(e.v2());
			else {
				if (it1 == it2)
					continue;
				else {
					it1->merge(*it2);
					disjointSet.erase(it2);
				}
			}
		}

		os << vertices[e.v1()].name()
			<< " - "
			<< vertices[e.v2()].name();

		MSTSize ++;

		if (MSTSize == vertices.size()-1) {
			break;
		}
		else {
			os << std::endl;
		}
	}

}
