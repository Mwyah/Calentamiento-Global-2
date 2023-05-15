//
// main.cpp
//

#include "MSTFinder.hpp"
#include "VertexParser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]) {


	if (argc == 3) {

		std::ifstream inputFile(argv[1]);
		std::ofstream outputFile(argv[2]);

		if (inputFile.is_open() && outputFile.is_open()) {
			outputFile.clear();

			MSTFinder allah;

			for (Vertex v = VertexParser::parse(inputFile); inputFile; v = VertexParser::parse(inputFile)) {
				allah.addVertex(v);
			}

			allah.findMST(outputFile);
		}

		if (inputFile.is_open()) inputFile.close();
		if (outputFile.is_open()) outputFile.close();
	}

	return EXIT_SUCCESS;
}