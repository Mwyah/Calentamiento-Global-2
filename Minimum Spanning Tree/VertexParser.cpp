//
// VertexParser.cpp
//

#include "VertexParser.hpp"


bool VertexParser::parse(std::istream& is) {

	if (!is) return false;

	for (std::string s; std::getline(is >> std::ws, s); ) {
		Output item;

		bool isValidInput = true;

		size_t ind1 = 0;
		for(size_t num = 0; num < 3; num++) {
			ind1 = s.find_first_not_of(" ,", ind1);

			if (ind1 == s.npos) break;

			size_t ind2 = s.find_first_of(" ,", ind1);
			size_t len = (ind2 == s.npos) ? s.size()-ind1 : ind2 - ind1;

			std::string arg = s.substr(ind1, len);
			if (num == 0)
				item.name = arg;
			if (num == 1 || num == 2) {
				size_t ind3 = 0;
				try {
					if (num == 1)
						item.x = std::stof(arg, &ind3);
					else
						item.y = std::stof(arg, &ind3);

					isValidInput = (ind3 == len);
				}
				catch (...){
					isValidInput = false;
				}
			}

			if (!isValidInput) break;

			ind1 = s.find_first_of(",", ind1);
		}

		if (isValidInput)
			output.push_back(std::move(item));
	}

	return true;
}