//
// HTMLColorizer.cpp
//

#include "HTMLColorizer.hpp"
#include "ReplaceHTMLEntities.hpp"

#include <algorithm>
#include <string>


namespace {
const std::string cornerSymbols = " .,\"()[]{}:;!?'<>";  // need to clarify
const std::string HTMLColorTag[] = {"<span style=\"color: #", ";\">", "</span>"};
}


void HTMLColorizer::addRule(const HTMLRule& rule) {
	if (!rule.empty() && 
		std::none_of(ruleList.begin(), ruleList.end(), [word = rule.word()](const HTMLRule r) { return r.word() == word; })) {
		ruleList.push_back(rule);
	}
}

void HTMLColorizer::colorize(std::istream& is, std::ostream& os) const {

	if (!is || !os) return;

	std::string str;
	while (std::getline(is, str)) {

		replace_HTML_entities(str);

		size_t wordBegin = str.find_first_not_of(cornerSymbols, 0);
		os << str.substr(0, wordBegin);

		if (!ruleList.empty()) {
			while (wordBegin != str.npos) {
				size_t wordEnd = str.find_first_of(cornerSymbols, wordBegin);

				size_t len = (wordEnd == str.npos) ? str.size()-wordBegin : wordEnd - wordBegin;
				std::string word = str.substr(wordBegin, len);

				auto it = std::find_if(ruleList.begin(), ruleList.end(), 
									   [word](const HTMLRule r){ return r.word() == word; });

				if (it != ruleList.end()) {
					os << HTMLColorTag[0] << it->color() << HTMLColorTag[1]
					   << it->word() << HTMLColorTag[2];
				}
				else {
					os << word;
				}

				if (wordEnd != str.npos) {
					wordBegin = str.find_first_not_of(cornerSymbols, wordEnd);
					len = (wordBegin == str.npos) ? str.size()-wordEnd : wordBegin - wordEnd;
					os << str.substr(wordEnd, len);
				}
			}
		}
		else {
			os << str.substr(wordBegin);
		}

		if (!is.eof()) {
			os << "\n";  //maybe "<br/>\n"
		}
	}
}