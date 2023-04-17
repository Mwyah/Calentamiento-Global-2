//
// main.cpp
//

#include "..\HTML Colorizer Lib\HTMLRuleParser.hpp"
#include <sstream>
#include <iostream>


int main() {

	std::istringstream rules("a : 111111\n   b: af3209\n cc d: aaaaaa aaaaaa\n n: b\n");

	HTMLRuleParser parser;
	parser.parse(rules);

	for (const HTMLRule& rule: parser)
		std::cout << rule.word << " : " << rule.color << std::endl;

	return EXIT_SUCCESS;
}