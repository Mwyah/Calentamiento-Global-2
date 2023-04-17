//
// MSTFinder.cpp
//

#include "MSTFinder.hpp"

#include <algorithm>
#include <ostream>

auto MSTFinder::findVertexInDisjointSet(size_t ind) {
	for (auto it = disjointSet.begin(); it != disjointSet.end(); it++) {
		if (std::find(it->begin(), it->end(), ind) != it->end())
			return it;
	}

	return disjointSet.end();
};

bool MSTFinder::addVertex(const Vertex& vertex) {

	if (std::find(vertices.begin(), vertices.end(), vertex) == vertices.end()) {

		vertices.push_back(vertex);
		isValidMST = false;

		return true;
	}

	return false;
}

bool MSTFinder::addVertex(Vertex&& vertex) {

	if (std::find(vertices.begin(), vertices.end(), vertex) == vertices.end()) {

		vertices.push_back(vertex);
		isValidMST = false;

		return true;
	}

	return false;
}

void MSTFinder::findMST() {

	if (isValidMST) return; 


	edges.clear();
	MST.clear();
	disjointSet.clear();

	fillAndSortVertices();

	for (auto& e: edges) {

		auto it1 = findVertexInDisjointSet(e.v1());
		auto it2 = findVertexInDisjointSet(e.v2());

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

		MST.push_back(e);

		if (MST.size() == vertices.size()-1) break;
	}

	isValidMST = true;

}

void MSTFinder::printMST(std::ostream& os) {

	findMST();

	for (const auto& e: MST) {
		os << vertices[e.v1()].name() 
		   << " - " 
		   << vertices[e.v2()].name() 
		   << std::endl;
	}
}


void MSTFinder::fillAndSortVertices() {
	for (size_t i = 0; i<vertices.size()-1; i++) {
		for (size_t j = i+1; j<vertices.size(); j++) {
			edges.push_back(Edge(vertices[i], vertices[j], i, j));
		}
	}

	std::sort(edges.begin(), edges.end());
}

void MSTFinder::printEdges(std::ostream& os) {

	findMST();

	for (const auto& e: edges) {
		os << vertices[e.v1()].name()
			<< " - "
			<< vertices[e.v2()].name()
			<< " " << e.length()
			<< std::endl;
	}
}
