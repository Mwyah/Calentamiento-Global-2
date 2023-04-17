//
// HTMLColorizer.cpp
//

#include "HTMLColorizer.hpp"

#include <algorithm>

void replace_HTML_entities(std::string& str);


void HTMLColorizer::addRule(const HTMLRule& rule) {
	if (ruleList.find(rule.word) == ruleList.end())
		ruleList.insert({rule.word, rule.color});
}

void HTMLColorizer::colorize(std::istream& is, std::ostream& os) const {

	if (!is || !os) return;

	std::regex re = createRegex();
	std::smatch m;

	std::string buf;
	while (std::getline(is, buf)) {

		replace_HTML_entities(buf);

		auto it = buf.cbegin();
		while (std::regex_search(it, buf.cend(), m, re)) {
			os << std::string(it, m[1].first) << m[1] << "<span style=\"color: #"
				<< ruleList.find(m[2].str())->second
				<< ";\">" << m[2] << "</span>" << m[3];

			it = m[3].second;
		}

		os << std::string(it, buf.cend());
		if (!is.eof()) os << "\n";
	}
}


//Private

std::regex HTMLColorizer::createRegex() const{

	std::string regexString(R"((\s|^|\.|;|:|!|,|\?)()");

	bool isFirstItem = true;
	for (const auto& it: ruleList) {
		if (!isFirstItem) regexString += "|";
		else isFirstItem = false;

		regexString += it.first;
	}

	regexString += R"()(\s|$|\.|;|:|!|,|\?))";

	return std::regex(regexString);
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