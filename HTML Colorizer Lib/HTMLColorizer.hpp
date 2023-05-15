//
// HTMLColorizer.hpp
//

#ifndef _CMG2_HTML_COLORIZER_HPP_
#define _CMG2_HTML_COLORIZER_HPP_

#include <string>
#include <regex>
#include <map>
#include "HTMLRule.hpp"


class HTMLColorizer final {
public:

	void addRule(const HTMLRule& rule);

	std::string colorize(const std::string& input) const;

private:
	std::vector<HTMLRule> ruleList;

};

#endif