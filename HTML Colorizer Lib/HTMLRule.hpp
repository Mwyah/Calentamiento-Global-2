//
// HTMLRule.hpp
//

#ifndef _CMG2_HTML_RULE_HPP_
#define _CMG2_HTML_RULE_HPP_

#include <string>


class HTMLRule final{
public:
	HTMLRule(): _word(""), _color("") {}

	HTMLRule(std::string word, std::string color) {
		this->_word = word;
		this->_color = color;
	}

	inline std::string word() const { return _word; }
	inline std::string color() const { return _color; }

	inline bool empty() const { return word().empty() && color().empty(); }

private:
	std::string _word;
	std::string _color;
};


#endif