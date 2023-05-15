//
// HTMLRuleParser.cpp
//

#include "HTMLRuleParser.hpp"
#include "ReplaceHTMLEntities.hpp"
#include <regex>
#include <exception>


namespace {

const std::regex colorRegex("([a-fA-F0-9]{6})");

const std::string tokenSeparators[] = {" :", ":"};

enum class ParseState {
	WORD = 0,
	COLOR = 1
};

ParseState& operator++(ParseState& ps) {
	int i = static_cast<int>(ps);
	++i;
	ps = static_cast<ParseState>(i);
	return ps;
}

}


HTMLRule HTMLRuleParser::parse(std::istream& is){

	if (!is) throw std::exception();

	std::string str;
	std::getline(is >> std::ws, str);

	std::string word, color;
	bool isValidInput = true;
	size_t tokenBegin = 0;

	for (ParseState parseState = ParseState::WORD; parseState <= ParseState::COLOR; parseState++) {
		tokenBegin = str.find_first_not_of(tokenSeparators[0], tokenBegin);

		if (tokenBegin == str.npos) {
			isValidInput = false;
			break;
		}

		size_t tokenEnd = str.find_first_of(tokenSeparators[0], tokenBegin);
		size_t len = (tokenEnd == str.npos) ? str.size()-tokenBegin : tokenEnd-tokenBegin;
		std::string token = str.substr(tokenBegin, len);

		if (parseState == WORD) {
			word = token;
		}
		else {
			if (std::regex_match(token, colorRegex)) color = token;
			else isValidInput = false;
		}

		if (!isValidInput) break;

		tokenBegin = str.find_first_of(tokenSeparators[1], tokenBegin);
	}

	if (isValidInput) {
		replace_HTML_entities(word);
		return HTMLRule(word, color);
	}
	else {
		return HTMLRule();
	}
}