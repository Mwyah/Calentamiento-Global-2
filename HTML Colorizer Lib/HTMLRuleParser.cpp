//
// HTMLRuleParser.cpp
//

#include "HTMLRuleParser.hpp"
#include <regex>

extern void replace_HTML_entities(std::string& str);  // HTMLColorizer.cpp


namespace {

const std::regex colorRegex("([a-fA-F0-9]{6})");

}


void HTMLRuleParser::parse(std::istream& is) {

	if (!is) return;

	for (std::string s; std::getline(is >> std::ws, s); ) {
		HTMLRule rule;
		bool isValidInput = true;
		size_t ind1 = 0;

		for (int parseState = 0; parseState < 2; parseState++) {
			ind1 = s.find_first_not_of(" :", ind1);

			if (ind1 == s.npos) break;

			size_t ind2 = s.find_first_of(" :", ind1);
			size_t len = (ind2 == s.npos) ? s.size()-ind1 : ind2 - ind1;
			std::string arg = s.substr(ind1, len);

			if (parseState == 0)
				rule.word = arg;
			else {
				if (std::regex_match(arg, colorRegex)) rule.color = arg;
				else isValidInput = false;
			}

			if (!isValidInput) break;

			ind1 = s.find_first_of(":", ind1);
		}

		if (isValidInput) {
			replace_HTML_entities(rule.word);
			output.push_back(std::move(rule));
		}

	}
}