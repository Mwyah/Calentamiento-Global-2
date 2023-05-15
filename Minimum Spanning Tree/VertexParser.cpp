//
// VertexParser.cpp
//

#include "VertexParser.hpp"


namespace {

const std::string tokenSeprators[] = {" ,", ","};

const size_t MAX_PARSE_STATE = 3;

enum ParseState {
	NAME = 0,
	X_COORD = 1,
	Y_COORD = 2
};

}


Vertex VertexParser::parse(std::istream& is) {

	if (!is) return Vertex("", 0, 0);

	std::string str; 
	std::getline(is >> std::ws, str);

	std::string name;
	float x = 0, y = 0;
	bool isValidInput = true;

	size_t tokenBegin = 0;
	for(size_t parseState = 0; parseState < MAX_PARSE_STATE; parseState++) {
		tokenBegin = str.find_first_not_of(tokenSeprators[0], tokenBegin);

		if (tokenBegin == str.npos) {
			isValidInput = false;
			break;
		}

		size_t tokenEnd = str.find_first_of(tokenSeprators[0], tokenBegin);
		size_t len = (tokenEnd == str.npos) ? str.size()-tokenBegin : tokenEnd - tokenBegin;

		std::string token = str.substr(tokenBegin, len);
		if (parseState == NAME) {
			name = token;
		}
		if (parseState == X_COORD || parseState == Y_COORD) {
			size_t stofInd = 0;
			try {
				if (parseState == X_COORD) {
					x = std::stof(token, &stofInd);
				}
				else {
					y = std::stof(token, &stofInd);
				}

				isValidInput = (stofInd == len);
			}
			catch (...){
				isValidInput = false;
			}
		}

		if (!isValidInput) break;

		tokenBegin = str.find_first_of(tokenSeprators[1], tokenBegin);
	}

	if (isValidInput) {
		return Vertex(name, x, y);
	}
	else {
		return Vertex("", 0, 0);
	}
}