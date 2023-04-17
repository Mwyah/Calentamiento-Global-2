//
// HTMLRuleParser.hpp
//

#ifndef _CMG2_HTML_RULE_PARSER_HPP_
#define _CMG2_HTML_RULE_PARSER_HPP_

#include <istream>
#include <vector>
#include "HTMLRUle.hpp"


class HTMLRuleParser final {
public:

	void parse(std::istream& is);

	inline auto begin() const { return output.cbegin(); }
	inline auto end() const { return output.cend(); }
	inline bool empty() const { return output.empty(); }
	inline size_t size() const { return output.size(); }

	inline void clear() { output.clear(); }

private:
	std::vector<HTMLRule> output;

};

#endif