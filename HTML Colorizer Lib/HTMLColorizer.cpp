//
// HTMLColorizer.cpp
//

#include "HTMLColorizer.hpp"

#include <algorithm>
#include <regex>


void HTMLColorizer::addRule(const HTMLRule& rule) {
	if (ruleList.find(rule.word) == ruleList.end())
		ruleList.insert({rule.word, rule.color});
}

void HTMLColorizer::colorize(std::istream& is, std::ostream& os) const {

	if (!is || !os) return;

	std::string ss;

	std::string regexString(R"((\s|^|\.|;|:|!|,|\?)()");

	bool isFirstItem = true;
	for (const auto& it: ruleList) {
		if (!isFirstItem) regexString += "|";
		else isFirstItem = false;

		regexString += it.first;
	}

	regexString += R"()(\s|$|\.|;|:|!|,|\?))";

	std::regex re(regexString);

	std::smatch m;

	std::regex_search(ss, );
}

void replace_HTML_entities(std::string& str) {
	char entities[] = {'&', '<', '>'};
	std::string replacers[] = {"&amp;", "&lt;", "&gt;"};

	for (int i = 0; i < 3; i++) {

		size_t pos = 0;
		while (true) {
			pos = str.find(entities[i], pos);

			if (pos == str.npos) break;

			str.replace(pos, 1, replacers[i]);

			pos += replacers[i].length();
		}
	}
}