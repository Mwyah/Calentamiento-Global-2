//
// HTMLRule.hpp
//

#ifndef _CMG2_HTML_RULE_HPP_
#define _CMG2_HTML_RULE_HPP_

#include <string>


class HTMLRule final{
public:
	HTMLRule(std::string word, std::string color) {
		if (word.empty() || color.empty()) {
			throw "???";
		}

		this->_word = word;
		this->_color = color;
	}

	inline std::string word() const { return _word; }
	inline std::string color() const { return _color; }
private:
	std::string _word;
	std::string _color;
};


#endif