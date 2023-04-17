//
// HTMLRule.hpp
//

#ifndef _CMG2_HTML_RULE_HPP_
#define _CMG2_HTML_RULE_HPP_

#include <string>


struct HTMLRule {
	std::string word;
	std::string color;
};


inline bool operator==(const HTMLRule& a, const HTMLRule& b) {
	return a.word == b.word;
}


#endif