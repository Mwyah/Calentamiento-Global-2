//
// HTMLColorizer.hpp
//

#ifndef _CMG2_HTML_COLORIZER_HPP_
#define _CMG2_HTML_COLORIZER_HPP_

#include <istream>
#include <regex>
#include <map>
#include "HTMLRule.hpp"


class HTMLColorizer final {
public:

	void addRule(const HTMLRule& rule);

	void colorize(std::istream& is, std::ostream& os) const;

private:
	std::map<std::string, std::string> ruleList;

	std::regex createRegex() const;

};

#endif