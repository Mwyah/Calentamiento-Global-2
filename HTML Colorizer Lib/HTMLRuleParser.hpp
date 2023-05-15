//
// HTMLRuleParser.hpp
//

#ifndef _CMG2_HTML_RULE_PARSER_HPP_
#define _CMG2_HTML_RULE_PARSER_HPP_

#include <istream>
#include "HTMLRule.hpp"


class HTMLRuleParser final {
public:
	HTMLRuleParser() = delete;

	static HTMLRule parse(std::istream& is);
};


class  final : public std::exception {
	inline const char* what() const { return ""; }
};

#endif