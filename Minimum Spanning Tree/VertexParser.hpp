//
// VertexParser.hpp
//

#ifndef _CMG2_VERTEX_PARSER_HPP_
#define _CMG2_VERTEX_PARSER_HPP_

#include <vector>
#include <iterator>
#include <string>
#include <fstream>


class VertexParser final {
public:

	struct Output {
		std::string name;
		float x = 0;
		float y = 0;
	};

	bool parse(std::istream& ifs);

	inline auto begin() { return output.cbegin(); }
	inline auto end() { return output.cend(); }
	inline bool empty() { return output.empty(); }
	inline size_t size() { return output.size(); }

	inline void clear() { output.clear(); }

private:
	std::vector<Output> output;

};


#endif