//
// main.cpp
//

#include "MSTFinder.hpp"
#include "VertexParser.hpp"

#include <iostream>
#include <sstream>


int main() {

	MSTFinder allah;

	/*std::vector<VertexParser::Output> input = {{"a", 0, 0}, {"b", 5, 5},
											   {"c", 7, -5}, {"d", -11, 3},
											   {"e", 7, 1}, {"f", 0, -2},
	                                           {"g", 2, 3}, {"h", 14, 7},
											   {"i", 3, 20}, {"j", 22, 0},
											   {"k", 7, -11}, {"l", 20, -22},
	                                           { "m", 3, -3}, {"n", -5, -5},
											   {"o", 9, -51}, {"p", -11, 30},
											   {"q", 72, 11}, {"r", 30, -20},
	                                           { "s", 10, 110}, {"t", 58, 35},
											   {"u", -77, -5}, {"v", -11, 13},
											   {"w", 71, 11}, {"x", 10, -12},
	                                           { "y", 7, 8}, {"z", 21, 12},
											   {"A", 74, -45}, {"B", -111, 13},
											   {"C", 27, 61}, {"D", 50, -52},
						                       { "E", 30, 20 }, {"F", 75, 15},
											   {"G", 17, -65}, {"H", -11, 83},
											   {"I", 72, 12}, {"J", 54, -32},
	                                           { "K", 10, -10 }, {"L", 53, 35},
											   {"M", 70, -50}, {"N", -11, 36},
											   {"O", 79, 91}, {"P", 40, -2}};

	for (auto& it: input) {
		allah.addVertex(it);
	}*/

	std::istringstream iss("a, 0.0, 0\n b n r, 5.77,,,, 5\n a,a,\n c, 7, -5\n d, -11, 3\n e, 7, 1\n f, 0, -2");

	VertexParser vp;
	vp.parse(iss);

	for (auto& it: vp) {
		std::cout << it.name << ' ' << it.x << ' ' << it.y << std::endl;
		allah.addVertex(it);
	}

	allah.printMST(std::cout);

	return EXIT_SUCCESS;
}